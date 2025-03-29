#pragma once
#include <iostream>
#include <SDL_TTF.h>
#include <string>

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
        void drawText(const std::string& text, Vector2f pos, SDL_Color color, int fontSize = 24);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
};