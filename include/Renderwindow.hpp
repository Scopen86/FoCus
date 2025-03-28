#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class RenderWindow {
public:
    RenderWindow();
    ~RenderWindow();
    bool init();
    void draw(std::string path, int p_x, int p_y, int p_w, int p_h);
    void clear();
    void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};