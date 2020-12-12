#include "voidMath.h"

void vec2D::setZero()
{
    x = 0.0f;
    y = 0.0f;
}

void vec2D::Set(const float& x_, const float& y_)
{
    x = x_;
    y = y_;
}

void vec2D::displayVector() const
{
    std::cout << "(" << x << "," << y << ")" << std::endl;
}

float vec2D::lenghtSquared() const
{
    return x * x + y * y;
}

float vec2D::lenght() const
{
    return sqrt(x * x + y * y);
}

void vec2D::operator+=(const vec2D &v)
{
    x += v.x; 
    y += v.y;
}

void vec2D::operator-=(const vec2D &v)
{
    x -= v.x;
    y -= v.y;
}

void vec2D::operator*=(const float &k)
{
    x *= k;
    y *= k;
}
