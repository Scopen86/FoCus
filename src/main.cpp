#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "RenderWindow.hpp"
#include "defs.hpp"
#include "Entity.hpp"

int main(int argc, char* argv[]) {
    RenderWindow window;
    bool gameRunning = true;
   
    SDL_Texture* backgroundTex = window.loadTexture("./res/background.jpg");
    SDL_Texture* playerTex = window.loadTexture("./res/player.png");
    SDL_Texture* enemyTex = window.loadTexture("./res/squareEnemy.png");

    Entity background(backgroundTex, Vector2f(0, 0), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    Entity player(playerTex, Vector2f(100, 100));
    Entity enemy(enemyTex, Vector2f(200, 200));
    
    SDL_Event event;
    while(gameRunning) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }
        
        window.clear();
        window.draw(background);
        window.draw(player);
        window.draw(enemy);
        window.display();
    }
    
    return 0;
}