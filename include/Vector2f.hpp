#pragma once
#include <iostream>

struct Vector2f
{
    float x, y;
    Vector2f()
        :x(0), y(0)
    {}
    Vector2f(float p_x, float p_y)
        :x(p_x), y(p_y)
    {}

    Vector2f operator+(const Vector2f& other) const
    {
        return Vector2f(x + other.x, y + other.y);
    }
    
    void print()
    {
        std::cout << "X: " << x << " Y: " << y << std::endl;
    }

};
