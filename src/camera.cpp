#include "defines.hpp"
#include "camera.hpp"

#include <sstream>
#include "physics.hpp" // For b2Vec2 stream operators

Camera::Camera(const b2Vec2 &worldMin, const b2Vec2 &worldMax,
               const b2Vec2 &screenMin, const b2Vec2 &screenMax,
               const b2Vec2 &screenMinInWorld, const b2Vec2 &screenMaxInWorld)
{
    setCamera(worldMin, worldMax,
              screenMin, screenMax,
              screenMinInWorld, screenMaxInWorld);
    //_rotationOrigin = b2Vec2();
    //_rotation = 0;
}

Camera::Camera(const b2Vec2 &worldMax,
               const b2Vec2 &screenMax,
               const b2Vec2 &screenMinInWorld,
               const b2Vec2 &screenMaxInWorld)
{
    setCamera(b2Vec2(0, 0), worldMax,
              b2Vec2(0, 0), screenMax,
              screenMinInWorld, screenMaxInWorld);
    //_rotationOrigin = b2Vec2();
    //_rotation = 0;
}

Camera::Camera(const b2Vec2 &worldMax,
               const b2Vec2 &screenMax)
{
    setCamera(b2Vec2(0, 0), worldMax,
              b2Vec2(0, 0), screenMax,
              b2Vec2(0, 0), worldMax);
}

void Camera::setCamera(const b2Vec2 &worldMin, const b2Vec2 &worldMax,
                       const b2Vec2 &screenMin, const b2Vec2 &screenMax,
                       const b2Vec2 &screenMinInWorld, const b2Vec2 &screenMaxInWorld)
{
    _scaleWorldToScreen.x = (screenMax.x - screenMin.x) /
                            (screenMaxInWorld.x - screenMinInWorld.x);
    _scaleWorldToScreen.y = (screenMax.y - screenMin.y) /
                            (screenMaxInWorld.y - screenMinInWorld.y);

    _scaleScreenToWorld.x = 1.f / _scaleWorldToScreen.x;
    _scaleScreenToWorld.y = 1.f / _scaleWorldToScreen.x;

    _screenMin = screenMin;
    _screenMax = screenMax;
    _worldMin = worldMin;
    _worldMax = worldMax;
    _screenMinInWorld = screenMinInWorld;
    _screenMaxInWorld = screenMaxInWorld;
}

b2Vec2 Camera::worldToScreen(const b2Vec2 &vec, bool invertYAxis) const
{
    b2Vec2 screen;
    screen.x = _screenMin.x + _scaleWorldToScreen.x *
            (vec.x - _worldMin.x - _screenMinInWorld.x);
    screen.y = _screenMin.y + _scaleWorldToScreen.y *
            (vec.y - _worldMin.y - _screenMinInWorld.y);

    if (invertYAxis)
    {
        screen.y = getScreenHeight() - screen.y;
    }

    return screen;
}

b2Vec2 Camera::screenToWorld(const b2Vec2 &vec, bool invertYAxis) const
{
    b2Vec2 world;
    world.x = (vec.x - _screenMin.x) * _scaleScreenToWorld.x +
            _worldMin.x + _screenMinInWorld.x;

    if (invertYAxis)
    {
        // Is this right?
        world.y = ((getScreenHeight() - vec.y) - _screenMin.y) * _scaleScreenToWorld.y +
                _worldMin.y + _screenMinInWorld.y;
    }
    else
    {
        world.y = (vec.y - _screenMin.y) * _scaleScreenToWorld.y +
                _worldMin.y + _screenMinInWorld.y;
    }

    return world;
}

float Camera::getWorldWidth() const
{
    return _worldMax.x - _worldMin.y;
}

float Camera::getWorldHeight() const
{
    return _worldMax.y - _worldMin.y;
}

float Camera::getScreenWidth() const
{
    return _screenMax.x - _screenMin.y;
}

float Camera::getScreenHeight() const
{
    return _screenMax.y - _screenMin.y;
}

void Camera::setScreenMin(const b2Vec2 &vec)
{
    setCamera(_worldMin, _worldMax,
              vec, _screenMax,
              _screenMinInWorld, _screenMaxInWorld);
}

void Camera::setScreenMax(const b2Vec2 &vec)
{
    setCamera(_worldMin, _worldMax,
              _screenMin, vec,
              _screenMinInWorld, _screenMaxInWorld);
}

void Camera::setWorldMin(const b2Vec2 &vec)
{
    setCamera(vec, _worldMax,
              _screenMin, _screenMax,
              _screenMinInWorld, _screenMaxInWorld);
}

void Camera::setWorldMax(const b2Vec2 &vec)
{
    setCamera(_worldMin, vec,
              _screenMin, _screenMax,
              _screenMinInWorld, _screenMaxInWorld);
}

void Camera::setScreenMinInWorld(const b2Vec2 &vec)
{
    setCamera(_worldMin, _worldMax,
              _screenMin, _screenMax,
              vec, _screenMaxInWorld);
}

void Camera::setScreenMaxInWorld(const b2Vec2 &vec)
{
    setCamera(_worldMin, _worldMax,
              _screenMin, _screenMax,
              _screenMinInWorld, vec);
}

void Camera::reshape(float x1, float y1, float x2, float y2)
{
    setCamera(_worldMin, _worldMax,
              b2Vec2(x1, y1), b2Vec2(x2, y2),
              _screenMinInWorld, _screenMaxInWorld);
}

void Camera::pan(const b2Vec2 &vec)
{
    setCamera(_worldMin, _worldMax,
              _screenMin, _screenMax,
              _screenMinInWorld + vec, _screenMaxInWorld + vec);
}

void Camera::zoom(const b2Vec2 &vec)
{
    setCamera(_worldMin, _worldMax,
              _screenMin, _screenMax,
              _screenMinInWorld + vec, _screenMaxInWorld - vec);
}

std::string Camera::toString() const
{
    std::ostringstream ss;
    ss << "Camera[worldMin = " << _worldMin << ", worldMax = " << _worldMax
       << ", screenMin = " << _screenMin << ", screenMax = " << _screenMax
       << ", screenMinInWorld = " << _screenMinInWorld
       << ", screenMaxInWorld = " << _screenMaxInWorld
       << ", scaleWorldToScreen = " << _scaleWorldToScreen
       << ", scaleScreenToWorld = " << _scaleScreenToWorld << "]";
    return ss.str();
}
