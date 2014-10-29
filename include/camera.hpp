#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include <easylogging++.h>
#include <iostream>

class Camera
{
public:
    Camera(const b2Vec2 &worldMin, const b2Vec2 &worldMax,
           const b2Vec2 &screenMin, const b2Vec2 &screenMax,
           const b2Vec2 &screenMinInWorld, const b2Vec2 &screenMaxInWorld);

    Camera(const b2Vec2 &worldMax,
           const b2Vec2 &screenMax,
           const b2Vec2 &screenMinInWorld,
           const b2Vec2 &screenMaxInWorld);

    Camera(const b2Vec2 &worldMax,
           const b2Vec2 &screenMax);

    void setCamera(const b2Vec2 &worldMin, const b2Vec2 &worldMax,
                   const b2Vec2 &screenMin, const b2Vec2 &screenMax,
                   const b2Vec2 &screenMinInWorld, const b2Vec2 &screenMaxInWorld);

    b2Vec2 worldToScreen(const b2Vec2 &vec, bool invertYAxis = false) const;
    b2Vec2 screenToWorld(const b2Vec2 &vec, bool invertYAxis = false) const;

    float getWorldWidth() const;
    float getWorldHeight() const;
    float getScreenWidth() const;
    float getScreenHeight() const;

    void setScreenMin(const b2Vec2 &vec);
    void setScreenMax(const b2Vec2 &vec);
    void setWorldMin(const b2Vec2 &vec);
    void setWorldMax(const b2Vec2 &vec);
    void setScreenMinInWorld(const b2Vec2 &vec);
    void setScreenMaxInWorld(const b2Vec2 &vec);

    void reshape(float x1, float y1, float x2, float y2);
    void pan(const b2Vec2 &vec);
    void zoom(const b2Vec2 &vec);
    //void rotate(float angle);

    std::string toString() const;

private:
    b2Vec2 _scaleWorldToScreen, _scaleScreenToWorld;
    b2Vec2 _screenMin, _screenMax;
    b2Vec2 _worldMin, _worldMax;
    b2Vec2 _screenMinInWorld, _screenMaxInWorld;
    //b2Vec2 _rotationOrigin;
    //float _rotation;
};

// Helper stream operators
template <class T>
inline std::ostream &operator<<(std::ostream &stream, const Camera &c)
{
    stream << c.toString();
    return stream;
}

inline MAKE_LOGGABLE(Camera, c, stream)
{
    stream << c.toString();
    return stream;
}

#endif
