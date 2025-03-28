#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
#include <vector>


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
        std::cout << "Failed to initialize SDL. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "Failed to initialize SDL_IMG. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    bool gameRunning = true;
   
    SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* background = IMG_LoadTexture(renderer, "./res/background.jpg");
    
    SDL_Event event;
    while(gameRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameRunning = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    return 0;
}