#include "defines.hpp"
#include <easylogging++.h>
#include <SDL2/SDL.h>
#include <tclap/CmdLine.h>
#include "game.hpp"
#include "level.hpp"

_INITIALIZE_EASYLOGGINGPP

// Locals
namespace
{
    const int DEFAULT_WINDOW_WIDTH = 640;
    const int DEFAULT_WINDOW_HEIGHT = 480;

    Game::Options parseArgs(int argc, char *argv[]);
}

int main(int argc, char *argv[])
{
    _START_EASYLOGGINGPP(argc, argv);

    try
    {
        Game::run(parseArgs(argc, argv));
    }
    catch (TCLAP::ArgException &e)
    {
        LOG(ERROR) << "ARG EXCEPTION: " << e.error();
        return 1;
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << "EXCEPTION: " << e.what();
        return 1;
    }

    LOG(INFO) << "shut down cleanly";
    return 0;
}

// Local functions
namespace {

Game::Options parseArgs(int argc, char *argv[])
{
    TCLAP::ValueArg<int> argWidth("w",
                                  "width",
                                  "window width",
                                  false,
                                  DEFAULT_WINDOW_WIDTH,
                                  "positive integer value");
    TCLAP::ValueArg<int> argHeight("h",
                                   "height",
                                   "window height",
                                   false,
                                   DEFAULT_WINDOW_HEIGHT,
                                   "positive integer value");
    TCLAP::CmdLine cmdLine("sdl", ' ', "0.1", false);

    cmdLine.add(argWidth);
    cmdLine.add(argHeight);
    cmdLine.parse(argc, argv);

    auto width = argWidth.getValue();
    auto height = argHeight.getValue();

    std::ostringstream ss;
    if (width < 0)
    {
        ss << "expected positive integer for window width (got "
           << width << ")";
        throw TCLAP::ArgException(ss.str());
    }
    else if (height < 0)
    {
        ss << "expected positive integer for window height (got "
           << height << ")";
        throw TCLAP::ArgException(ss.str());
    }

    return Game::Options { width, height };
}

}
