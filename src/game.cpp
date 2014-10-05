#include "game.hpp"

#include <algorithm>
#include <easylogging++.h>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <tclap/CmdLine.h>
#include "asteroid.hpp"
#include "exception.hpp"
#include "ship.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "timer.hpp"

static const int NUM_ASTEROIDS = 5;

static bool _running;
static std::map<game::EventHandle, std::shared_ptr<game::Event>> _events;
static Timer _fpsTimer;

static std::shared_ptr<Ship> _ship;
static std::list<std::shared_ptr<Asteroid>> _asteroids;
static std::list<std::shared_ptr<Entity>> _collidables;

static void initSDL();
static void shutdownSDL();
static void initSprites();
static void destroySprites();
static void registerEvents();
static void handleEvents();
static void updateEntities(float dt);
static void checkCollisions(float dt);
static void drawScene();

class KeyEvent : public game::Event
{
public:
    KeyEvent(SDL_Keycode key,
             game::EventCallback callback,
             const std::string debugString_) :
        Event(debugString_),
        _key(key),
        _callback(callback) {}

    bool test(const SDL_Event &e)
    {
        return (e.type == SDL_KEYDOWN &&
                e.key.keysym.sym == _key);
    }

    void fire()
    {
        _callback();
    }

private:
    SDL_Keycode _key;
    game::EventCallback _callback;
};

class QuitEvent : public game::Event
{
public:
    using game::Event::Event;

    bool test(const SDL_Event &e)
        { return (e.type == SDL_QUIT); }
    void fire()
        { game::setRunning(false); }
};

int game::run(game::Options options)
{
    try
    {
        initSDL();
        window::create(options.windowWidth, options.windowHeight);
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << "EXCEPTION: " << e.what();
        return 1;
    }

    registerEvents();
    initSprites();

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
            window::setTitle(ss.str());
            oldTicks = currentTicks;
        }

        try
        {
            handleEvents();

            dt = stepTimer.getTicks() / 1000.f;
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

    destroySprites();
    shutdownSDL();
    return 0;
}

bool game::isRunning()
{
    return _running;
}

void game::setRunning(bool b)
{
    _running = b;
}

game::EventHandle game::registerEvent(SDL_Keycode key,
                                      game::EventCallback callback,
                                      const std::string &debugString)
{
    return registerEvent(std::shared_ptr<KeyEvent>(
                             new KeyEvent(key, callback, debugString)));
}

game::EventHandle game::registerEvent(std::shared_ptr<game::Event> event)
{
    static EventHandle currentHandle = 0;

    _events[++currentHandle] = event;

    if (!event->debugString.empty())
        LOG(DEBUG) << "registered event " << event->debugString;
    return currentHandle;
}

void game::unregisterEvent(game::EventHandle handle)
{
    auto i = _events.find(handle);
    if (!i->second->debugString.empty())
        LOG(DEBUG) << "unregistered event " << i->second->debugString;
    _events.erase(i);
}

void game::registerCollidable(std::shared_ptr<Entity> entity)
{
    _collidables.push_back(entity);
    LOG(DEBUG) << "registered collidable entity " << entity->getName();
}

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
        LOG(INFO) << "using SDL " << (int)version.major << "."
                  << (int)version.minor << "." << (int)version.patch;
    }

    auto flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(flags) & flags))
    {
        SDL_Quit();
        throw SDLImageException();
    }
}

void shutdownSDL()
{
    window::destroy();
    IMG_Quit();
    SDL_Quit();
}

void initSprites()
{
    _ship = std::shared_ptr<Ship>(new Ship(window::getWidth() / 2,
                                           window::getHeight() / 2));
    game::registerCollidable(_ship);

    // This should probably test for overlap and repeated numbers, but meh
    std::default_random_engine generator;
    std::uniform_int_distribution<int> x_distribution(0, window::getWidth());
    std::uniform_int_distribution<int> y_distribution(0, window::getHeight());
    for (int i = 0; i < NUM_ASTEROIDS; i++)
    {
        std::ostringstream ss;
        ss << "Asteroid" << i;

        int x = x_distribution(generator);
        int y = y_distribution(generator);
        auto asteroid = std::shared_ptr<Asteroid>(new Asteroid(ss.str(), x, y));
        _asteroids.push_back(asteroid);
        game::registerCollidable(asteroid);

        LOG(DEBUG) << "creating asteroid " << ss.str() << "(" << x << ", " << y << ")";
    }
}

void destroySprites()
{
    _collidables.clear();
    _asteroids.clear();
    //_ship.reset();
}

void registerEvents()
{
    game::registerEvent(std::shared_ptr<game::Event>(
                            new QuitEvent("QuitEvent")));
    game::registerEvent(SDLK_ESCAPE,
                        []() { game::setRunning(false); },
                        "EscapeEvent");
    game::registerEvent(SDLK_SPACE, []()
    {
        switch (_fpsTimer.getState())
        {
        case TimerState::RUNNING:
            _fpsTimer.pause();
            break;

        case TimerState::PAUSED:
            _fpsTimer.resume();
            break;

        case TimerState::STOPPED:
            LOG(WARNING) << "timer isn't running (why?)";
        }
    }, "TimerToggleEvent");
}

void handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        for (auto &pair : _events)
        {
            if (pair.second->test(event)) pair.second->fire();
        }
    }
}

void updateEntities(float dt)
{
    _ship->update(dt);

    for (auto &asteroid : _asteroids)
    {
        asteroid->update(dt);
    }

    checkCollisions(dt);
}

void checkCollisions(float dt)
{
    for (auto &entity : _collidables)
    {
        for (auto &other : _collidables)
        {
            if (entity != other)
            {
                auto entityBB = entity->getBoundingBox();
                auto otherBB = other->getBoundingBox();
                SDL_Rect intersection;
                if (SDL_IntersectRect(&entityBB, &otherBB, &intersection))
                {
                    entity->collide(dt, other, intersection);
                }
            }
        }
    }
}

void drawScene()
{
    window::clear();

    _ship->draw();

    for (auto &asteroid : _asteroids)
    {
        asteroid->draw();
    }

    window::flip();
}
