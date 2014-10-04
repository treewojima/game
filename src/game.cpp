#include "game.hpp"

#include <algorithm>
#include <easylogging++.h>
#include <map>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <tclap/CmdLine.h>
#include <vector>
#include "exception.hpp"
#include "ship.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "timer.hpp"

static bool _running;
static std::map<game::EventHandle, std::shared_ptr<game::Event>> _events;
static std::unique_ptr<Ship> _ship;
static Timer _fpsTimer;

static void initSDL();
static void shutdownSDL();
static void initSprites();
static void destroySprites();
static void registerEvents();
static void handleEvents();

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

    int countedFrames = 0;
    Uint32 oldTicks = 0, currentTicks = 0;
    setRunning(true);
    _fpsTimer.start();
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

            window::clear();
            _ship->draw();
            window::flip();
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
    return registerEvent(new KeyEvent(key, callback, debugString));
}

game::EventHandle game::registerEvent(game::Event *event)
{
    static EventHandle currentHandle = 0;

    _events[++currentHandle] = std::shared_ptr<Event>(event);

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
    _ship = std::unique_ptr<Ship>(new Ship(window::getWidth(),
                                           window::getHeight()));
}

void destroySprites()
{
    _ship.reset();
}

void registerEvents()
{
    game::registerEvent(new QuitEvent("QuitEvent"));
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
        std::for_each(_events.begin(), _events.end(),
                      [&] (std::pair<game::EventHandle,
                                     std::shared_ptr<game::Event>> pair)
        {
            if (pair.second->test(event)) pair.second->fire();
        });
    }
}
