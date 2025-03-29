#pragma once
#include <iostream>

#include "Entity.hpp"

class RenderWindow {
public:
    RenderWindow();
    ~RenderWindow();
    bool init();
    SDL_Texture* loadTexture(const std::string& filePath);
    void draw(Entity& entity);
    void clear();
    void display();
    void shake(int direction);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};