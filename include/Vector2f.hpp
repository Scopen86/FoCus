#pragma once
#include <iostream>
#include <cmath>

struct Vector2f
{
    float x, y;
    Vector2f()
        :x(0), y(0)
    {}
    Vector2f(float p_x, float p_y)
        :x(p_x), y(p_y)
    {}

    float getDistance(const Vector2f& other) const
    {
        return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }

    Vector2f operator+(const Vector2f& other) const
    {
        return Vector2f(x + other.x, y + other.y);
    }

    Vector2f operator*(float scalar) const {
        return Vector2f(x * scalar, y * scalar);
    }

    Vector2f operator/(float scalar) const {
        if (scalar != 0) {
            return Vector2f(x / scalar, y / scalar);
        } else {
            std::cout << "Error: Division by zero in Vector2f." << std::endl;
            return Vector2f(0, 0);
        }
    }

    void print()
    {
        std::cout << "X: " << x << " Y: " << y << std::endl;
    }

};
