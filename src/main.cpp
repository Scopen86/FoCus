#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "RenderWindow.hpp"
#include "defs.hpp"

int main(int argc, char* argv[]) {
    bool gameRunning = true;
   
    std::string background = "./res/background.jpg";
    std::string player = "./res/player.png";
    RenderWindow window;
    
    SDL_Event event;
    while(gameRunning) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }
        
        window.clear();
        window.draw(background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        window.draw(player, 100, 100, 50, 50);
        window.display();
    }

    return 0;
}