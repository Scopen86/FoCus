#include <iostream>

#include "RenderWindow.hpp"
#include "defs.hpp"

RenderWindow::RenderWindow() {
    init();
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

RenderWindow::~RenderWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

bool RenderWindow::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
        std::cout << "Failed to initialize SDL. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cout << "Failed to initialize SDL_IMG. Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void RenderWindow::draw(std::string path, int p_x, int p_y, int p_w, int p_h) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) {
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
        std::cout << "Path: " << path << std::endl;
        return;
    }
    else {
        std::cout << "Loaded texture at " << path << std::endl;
    }

    SDL_Rect destRect = { p_x, p_y, p_w, p_h };

    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}

void RenderWindow::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}