#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include "defines.hpp"
#include <GL/glew.h>
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

class GLException : public Exception
{
public:
    GLException(const std::string &msg) : Exception(msg) {}
    explicit GLException(GLenum error) : Exception(getErrorString(error)) {}

private:
    std::string getErrorString(GLenum error)
    {
        std::ostringstream ss;
        ss << gluErrorString(error);
        return ss.str();
    }
};

class GLEWException : public GLException
{
public:
    GLEWException(const std::string &msg) : GLException(msg) {}
    explicit GLEWException(GLenum error) : GLException(getErrorString(error)) {}

private:
    std::string getErrorString(GLenum error)
    {
        std::ostringstream ss;
        ss << glewGetErrorString(error);
        return ss.str();
    }
};

class PhysicsException : public Exception
{
public:
    using Exception::Exception;
};

#endif
