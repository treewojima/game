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
#include "texture.hpp"

static std::unique_ptr<Window> _window;
static std::unique_ptr<Texture> _texture;
static bool _running;
static std::vector<std::shared_ptr<game::Event>> _events;

static void handleEvents();

class KeyEvent : public game::Event
{
public:
    KeyEvent(SDL_Keycode key, game::EventCallback callback) :
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

int game::run(game::Options options)
{
    try
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

        _window = std::unique_ptr<Window>(new Window(options.windowWidth,
                                                     options.windowHeight));

        _texture = std::unique_ptr<Texture>(new Texture("res/textures/tux.png"));
    }
    catch (std::exception &e)
    {
        LOG(FATAL) << "EXCEPTION: " << e.what();
        return 1;
    }

    setRunning(true);
    while (isRunning())
    {
        try
        {
            handleEvents();

            getWindow().clear();
            SDL_RenderCopy(getWindow().getRenderer(),
                           _texture->getRawTexture(),
                           nullptr, nullptr);
            getWindow().flip();
        }
        catch (std::exception &e)
        {
            LOG(FATAL) << "EXCEPTION: " << e.what();
            setRunning(false);
        }
    }

    //_events.clear();
    _texture.reset();
    _window.reset();
    IMG_Quit();
    SDL_Quit();
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

Window &game::getWindow()
{
    return *_window;
}

void game::registerEvent(SDL_Keycode key, game::EventCallback callback)
{
    // TODO: test if map already contains a registered key, as well as other
    //       error checking

    registerEvent(new KeyEvent(key, callback));
}

void game::registerEvent(game::Event *event)
{
    _events.push_back(std::shared_ptr<Event>(event));
}

void handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        std::for_each(_events.begin(), _events.end(),
                      [&] (std::shared_ptr<game::Event> e)
        {
            if (e->test(event)) e->fire();
        });
    }
}
