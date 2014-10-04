#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include "defines.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <stdexcept>
#include <string>

class Exception : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class SDLException : public Exception
{
public:
    SDLException(const std::string &msg) : Exception(msg) {}
    SDLException() : Exception(SDL_GetError()) {}
};

class SDLImageException : public SDLException
{
public:
    SDLImageException(const std::string &msg) : SDLException(msg) {}
    SDLImageException() : SDLException(IMG_GetError()) {}
};

#endif
