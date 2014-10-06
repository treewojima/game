#ifndef __MATH_HPP__
#define __MATH_HPP__

#include "defines.hpp"
#include <cmath>
#include <iostream>

// Templated two-dimensional vector class
template <class T>
class Vector2
{
public:
    T x, y;

    // Constructors
    Vector2() : x(0), y(0) {}
    Vector2(const T x_, const T y_) : x(x_), y(y_) {}
    Vector2(const Vector2<T> &v) : x(v.x), y(v.y) {}

    // Normalization
    Vector2<T> normalize()
    {
        auto length = getLength();
        if (length == 0) y = 1;
        x /= length;
        y /= length;
        return *this;
    }

    // Reflection
    Vector2<T> reflect(Vector2<T> v)
    {
        auto unitNormal = v.normalize();
        *this = *this - (unitNormal * ((*this * unitNormal) * 2));
        return *this;
    }

    // Length
    inline float getLength() const
    {
        return std::sqrt(x * x + y * y);
    }

    // Angle in radians
    inline float getAngle() const
    {
        return std::atan2(y, x);
    }

    // Angle in degrees
    inline float getAngleDeg() const
    {
        return getAngle() * (180 / M_PI);
    }

    // Assignment operator
    Vector2<T> &operator=(Vector2<T> v)
    {
        std::swap(x, v.x);
        std::swap(y, v.y);
        return *this;
    }

    // Indexing operators
    T &operator[](const unsigned i) { return *(&x + i); }
    const T &operator[](const unsigned i) const { return *(&x + i); }

    // Compound addition operator
    Vector2<T> &operator+=(const Vector2<T> &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    // Compound subtraction operator
    Vector2<T> &operator-=(const Vector2<T> &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    // Compound scalar multiplication operator
    Vector2<T> &operator*=(const float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Compound scalar division operator
    Vector2<T> &operator/=(const float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

// Equality operator
template <class T>
bool operator==(const Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

// Inequality operator
template <class T>
bool operator!=(const Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

// Addition operator
template <class T>
Vector2<T> operator+(Vector2<T> lhs, const Vector2<T> &rhs)
{
    return lhs += rhs;
}

// Subtraction operator
template <class T>
Vector2<T> operator-(Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return lhs -= rhs;
}

// Negation operator
template <class T>
Vector2<T> operator-(const Vector2<T> &v)
{
    return Vector2<T>(-v.x, -v.y);
}

// Scalar multiplication operator
template <class T>
Vector2<T> operator*(Vector2<T> v, const float scalar)
{
    return v *= scalar;
}

// Scalar division operator
template <class T>
Vector2<T> operator/(Vector2<T> v, const float scalar)
{
    return v /= scalar;
}

// Dot product operator
template <class T>
T operator*(const Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

// Cross product operator
template <class T>
T operator^(const Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

// Global normalization function
template <class T>
Vector2<T> normalize(Vector2<T> v)
{
    return v.normalize();
}

// Stream operator
template <class T>
std::ostream &operator<<(std::ostream &stream, Vector2<T> v)
{
    stream << "(" << v.x << ", " << v.y << ")";
    return stream;
}

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;

void testMath();

#endif
