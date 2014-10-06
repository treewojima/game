#include "defines.hpp"
#include "math.hpp"

#include <iostream>

void testMath()
{
    Vector2f vec(5, 7), vec2(1, 1);
    std::cout << vec.reflect(vec2) << std::endl;
}
