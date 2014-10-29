#include "defines.hpp"
#include "game.hpp"

#include <algorithm>
#include <Box2D/Box2D.h>
#include <easylogging++.h>
#include <GL/glew.h>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <tclap/CmdLine.h>

#include "entities/block.hpp"
#include "entities/ground.hpp"
#include "entities/player.hpp"
#include "entity.hpp"
#include "exception.hpp"
#include "physics.hpp"
#include "texture.hpp"
#include "timer.hpp"

// Locals
namespace
{
    const int NUM_BLOCKS = 2;

    bool _running = false;
    bool _trackMouseMotion = false;
    bool _stepPhysics = true;
    std::map<Game::Event::Handle, std::shared_ptr<Game::Event>> _events;
    Timer _fpsTimer;
    std::unique_ptr<Camera> _camera;

    std::shared_ptr<Player> _player;
#ifdef _ENABLE_GROUND
    std::shared_ptr<Ground> _ground;
#endif
#ifdef _ENABLE_BLOCKS
    std::list<std::shared_ptr<Block>> _blocks;
#endif

    void initSDL();
    void initGL();
    void shutdownSDL();
    void initEntities();
    void destroyEntities();
    void registerEvents();
    void handleEvents();
    void updateEntities(float dt);
    void drawScene();

    // Helper key handler event for registerEvent()
    class KeyEvent : public Game::Event
    {
    public:
        KeyEvent(SDL_Keycode key,
                 Game::Event::Callback callback,
                 const std::string debugString_) :
            Event(debugString_),
            _key(key),
            _callback(callback) {}

        bool test(const SDL_Event &e)
        {
            return (e.type == SDL_KEYDOWN &&
                    e.key.keysym.sym == _key);
        }

        void fire(const SDL_Event &e)
        {
            _callback(e);
        }

    private:
        SDL_Keycode _key;
        Game::Event::Callback _callback;
    };

    // Program quit handling event, for signals such as ^C
    class QuitEvent : public Game::Event
    {
    public:
        QuitEvent() : Game::Event("QuitEvent") {}

        bool test(const SDL_Event &e)
            { return (e.type == SDL_QUIT); }

        void fire(const SDL_Event &e)
        {
            Game::setRunning(false);
            LOG(INFO) << "received quit signal";
        }
    };

    // Mouse tracking event
    class MouseMotionEvent : public Game::Event
    {
    public:
        MouseMotionEvent() : Game::Event("MouseMotionEvent") {}

        bool test(const SDL_Event &e)
        {
            return (_trackMouseMotion && e.type == SDL_MOUSEMOTION &&
                    (e.motion.xrel || e.motion.yrel));
        }

        void fire(const SDL_Event &e)
        {
            std::cout << "mouse movement: abs("
                      << e.motion.x << ", "
                      << e.motion.y << "), rel("
                      << e.motion.xrel << ", "
                      << e.motion.yrel << ")"
                      << std::endl;
        }
    };
}

int Game::run(Game::Options options)
{
    try
    {
        initSDL();
        Window::create(options.windowWidth, options.windowHeight);

        auto screenRatio = static_cast<float>(options.windowWidth) /
                           static_cast<float>(options.windowHeight);
        _camera = std::unique_ptr<Camera>(
            new Camera(b2Vec2(0, 0),                                      // worldMin
                       b2Vec2(10 * screenRatio, 10),                      // worldMax
                       b2Vec2(0, 0),                                      // screenMin
                       b2Vec2(options.windowWidth, options.windowHeight), // screenMax
                       b2Vec2(0, 0),                                      // screenMinInWorld
                       b2Vec2(10 * screenRatio, 10)));                    // screenMaxInWorld
        //LOG(DEBUG) << *_camera;

        initGL();
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << "EXCEPTION: " << e.what();
        return 1;
    }

    Physics::initialize();
    initEntities();
    registerEvents();

    Timer stepTimer;
    float dt = 0;

    int countedFrames = 0;
    Uint32 oldTicks = 0, currentTicks = 0;

    setRunning(true);
    _fpsTimer.start();
    stepTimer.start();
    while (isRunning())
    {
        // Update the FPS counter every second or so
        currentTicks = _fpsTimer.getTicks();
        if (currentTicks - oldTicks >= 1000)
        {
            float avgFPS = countedFrames / (currentTicks / 1000.f);
            std::ostringstream ss;
            ss << "FPS: " << avgFPS;
            Window::setTitle(ss.str());
            oldTicks = currentTicks;
        }

        try
        {
            handleEvents();

            dt = stepTimer.getTicks() / 1000.f;
            if (_stepPhysics) Physics::step(dt);
            updateEntities(dt);
            stepTimer.start();

            drawScene();
        }
        catch (std::exception &e)
        {
            LOG(ERROR) << "EXCEPTION: " << e.what();
            setRunning(false);
        }

        countedFrames++;
    }
    _fpsTimer.stop();

    Window::destroy();
    destroyEntities();
    shutdownSDL();
    return 0;
}

bool Game::isRunning()
{
    return _running;
}

void Game::setRunning(bool b)
{
    _running = b;
}

Camera &Game::getCamera()
{
    return *_camera;
}

Game::Event::Handle Game::registerEvent(SDL_Keycode key,
                                      Game::Event::Callback callback,
                                      const std::string &debugString)
{
    return registerEvent(std::shared_ptr<KeyEvent>(
                             new KeyEvent(key, callback, debugString)));
}

Game::Event::Handle Game::registerEvent(std::shared_ptr<Game::Event> event)
{
    static Event::Handle currentHandle = 0;

    _events[++currentHandle] = event;

#ifdef _DEBUG_EVENTS
    if (!event->debugString.empty())
        LOG(DEBUG) << "registered event " << event->debugString;
#endif

    return currentHandle;
}

void Game::unregisterEvent(Game::Event::Handle handle)
{
#ifdef _DEBUG_EVENTS
    //LOG(DEBUG) << "trying to unregister event handle " << handle;
    if (_events.count(handle))
        LOG(DEBUG) << "unregistered event " << _events[handle]->debugString;
#endif

    _events.erase(handle);
}

// Local functions
namespace {

void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        throw SDLException();
    }
    else
    {
        SDL_version version;
        SDL_GetVersion(&version);
        LOG(INFO) << "using SDL " << static_cast<int>(version.major) << "."
                  << static_cast<int>(version.minor) << "."
                  << static_cast<int>(version.patch);
    }

    auto flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(flags) & flags))
    {
        SDL_Quit();
        throw SDLImageException();
    }
}

void initGL()
{
    auto errorCode = glewInit();
    if (errorCode != GLEW_OK)
        throw GLEWException(errorCode);

    LOG(INFO) << "using GLEW " << glewGetString(GLEW_VERSION);
    LOG(INFO) << "using OpenGL " << glGetString(GL_VERSION);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    /*glClearColor(0, 0, 0, 0);
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT);*/

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    auto screenMinInWorld = _camera->getScreenMinInWorld();
    auto screenMaxInWorld = _camera->getScreenMaxInWorld();
    gluOrtho2D(screenMinInWorld.x, screenMaxInWorld.x,
               screenMinInWorld.y, screenMaxInWorld.y);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    errorCode = glGetError();
    if (errorCode != GL_NO_ERROR)
        throw GLException(errorCode);
}

void shutdownSDL()
{
    IMG_Quit();
    SDL_Quit();
}

void initEntities()
{
    auto pos = b2Vec2(_camera->getWorldWidth() / 4,
                      _camera->getWorldHeight() / 2);
    _player = std::make_shared<Player>(pos);
    _player->initialize();
    LOG(DEBUG) << *_player;

#ifdef _ENABLE_GROUND
    _ground = std::make_shared<Ground>(
            "Ground",
            b2Vec2(-Window::getWidth(), 0),
            b2Vec2(Window::getWidth() * 3, Ground::DEFAULT_HEIGHT),
            false);
    _ground->initialize();
    LOG(DEBUG) << *_ground;
#endif

#ifdef _ENABLE_BLOCKS
    // This should probably test for overlap and repeated numbers, but meh
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float>
            x_distribution(0, Window::getWidth() - Block::DEFAULT_WIDTH);
    std::uniform_real_distribution<float>
            y_distribution(0, Window::getHeight() - Block::DEFAULT_HEIGHT);
    for (int i = 0; i < NUM_BLOCKS; i++)
    {
        std::ostringstream ss;
        ss << "Block" << i;
        float x = x_distribution(generator);
        float y = y_distribution(generator);

        auto block = std::make_shared<Block>(
                ss.str(),
                b2Vec2(x, y),
                b2Vec2(Block::DEFAULT_WIDTH, Block::DEFAULT_HEIGHT));
        block->initialize();
        _blocks.push_back(block);

        //LOG(DEBUG) << "creating block " << ss.str() << "(" << x << ", " << y << ")";
    }
#endif
}

void destroyEntities()
{
    // Warning: this invalidates ALL entity smart pointers!

#ifdef _ENABLE_BLOCKS
    for (auto &block : _blocks)
        block.reset();
#endif

    _player.reset();

#ifdef _ENABLE_GROUND
    _ground.reset();
#endif
}

void registerEvents()
{
    Game::registerEvent(std::make_shared<QuitEvent>());

    Game::registerEvent(
            SDLK_ESCAPE,
            [](const SDL_Event &e) { Game::setRunning(false); },
            "EscapeEvent");

    Game::registerEvent(
            SDLK_m,
            [&](const SDL_Event &e) { _trackMouseMotion = !_trackMouseMotion; },
            "MouseMotionToggleEvent");
    Game::registerEvent(std::make_shared<MouseMotionEvent>());

    Game::registerEvent(
            SDLK_s,
            [&](const SDL_Event &e) { _stepPhysics = !_stepPhysics; },
            "StepPhysicsToggleEvent");
}

void handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        for (auto &pair : _events)
        {
            if (pair.second->test(event)) pair.second->fire(event);
        }
    }
}

void updateEntities(float dt)
{
    _player->update(dt);

#ifdef _ENABLE_GROUND
    _ground->update(dt);
#endif

#ifdef _ENABLE_BLOCKS
    for (auto &block : _blocks)
        block->update(dt);
#endif
}

void drawScene()
{
    Window::clear(1, 1, 1);

    _player->draw();

#ifdef _ENABLE_GROUND
    _ground->draw();
#endif

#ifdef _ENABLE_BLOCKS
    for (auto &block : _blocks)
        block->draw();
#endif

    Window::flip();
}

}
