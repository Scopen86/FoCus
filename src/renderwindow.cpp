#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

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

void RenderWindow::draw(Entity& entity) {
    SDL_Texture* texture = entity.getTex();
    Vector2f pos = entity.getPosition();
    Vector2f size = entity.getSize();

    SDL_Rect destRect = { 
        static_cast<int> (pos.x),
        static_cast<int> (pos.y),
        static_cast<int> (size.x),
        static_cast<int> (size.y)
    };

    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

SDL_Texture* RenderWindow::loadTexture(const std::string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        std::cout << "Failed to load texture. Error: " << IMG_GetError() << std::endl;
    }
    return texture;
}

void RenderWindow::shake(int direction) {
    int shakeAmount = 10; 
    int shakeDuration = 10; // milliseconds
    
    int x, y;
    SDL_GetWindowPosition(window, &x, &y);
    
    switch(direction) {
        case 0: // Up
            for(int i = 0; i < shakeDuration / 10; ++i) {
                SDL_SetWindowPosition(window, x, y - shakeAmount);
                SDL_Delay(10);
                SDL_SetWindowPosition(window, x, y + shakeAmount);
                SDL_Delay(10);
            }
            break;
        case 1: // Down
            for(int i = 0; i < shakeDuration / 10; ++i) {
                SDL_SetWindowPosition(window, x, y + shakeAmount);
                SDL_Delay(10);
                SDL_SetWindowPosition(window, x, y - shakeAmount);
                SDL_Delay(10);
            }
            break;
        case 2: // Left
            for(int i = 0; i < shakeDuration / 10; ++i) {
                SDL_SetWindowPosition(window, x - shakeAmount, y);
                SDL_Delay(10);
                SDL_SetWindowPosition(window, x + shakeAmount, y);
                SDL_Delay(10);
            }
            break;
        case 3: // Right
            for(int i = 0; i < shakeDuration / 10; ++i) {
                SDL_SetWindowPosition(window, x + shakeAmount, y);
                SDL_Delay(10);
                SDL_SetWindowPosition(window, x - shakeAmount, y);
                SDL_Delay(10);
            }
            break;
        default:
            std::cout << "Shaking in all directions." << std::endl;
            this->shake(0);
            this->shake(1);
            this->shake(2);
            this->shake(3);
            break;
    }
    // Reset window position
    SDL_SetWindowPosition(window, x, y);
}