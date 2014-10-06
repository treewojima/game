#include "defines.hpp"
#include <easylogging++.h>
#include <SDL2/SDL.h>
#include <tclap/CmdLine.h>
#include "game.hpp"
#include "math.hpp"

_INITIALIZE_EASYLOGGINGPP

static const int DEFAULT_WINDOW_WIDTH = 640;
static const int DEFAULT_WINDOW_HEIGHT = 480;

static game::Options parseArgs(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    _START_EASYLOGGINGPP(argc, argv);

    try
    {
        game::run(parseArgs(argc, argv));
    }
    catch (TCLAP::ArgException &e)
    {
        LOG(ERROR) << "ARG EXCEPTION: " << e.error();
        return 1;
    }

    return 0;
}

game::Options parseArgs(int argc, char *argv[])
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
    TCLAP::CmdLine cmdLine("opengl test", ' ', "0.1", false);

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

    return game::Options { width, height };
}
