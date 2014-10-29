#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "defines.hpp"
#include <memory>

namespace Window
{
    void create(int width, int height);
    void destroy();

    void clear(float r = 0, float g = 0, float b = 0, float a = 0);
    //void blitTexture(const Texture &texture, int x, int y);
    void flip();

    void setTitle(const std::string &title);

    //float getWidth();
    //float getHeight();
    //int getWidthPixels();
    //int getHeightPixels();
}

#endif
