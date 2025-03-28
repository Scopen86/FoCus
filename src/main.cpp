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

        // Handle player movement
        Vector2f deltaPos(0, 0);
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
            deltaPos.y -= player.getSpeed();
        }
        if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
            deltaPos.y += player.getSpeed();
        }
        if(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
            deltaPos.x -= player.getSpeed();
        }
        if(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
            deltaPos.x += player.getSpeed();
        }
        player.move(deltaPos);

        // Prevent player from going off screen
        Vector2f playerPos = player.getPosition();
        if(playerPos.x < 0) player.setPos(Vector2f(0, playerPos.y));
        if(playerPos.y < 0) player.setPos(Vector2f(playerPos.x, 0));
        if(playerPos.x + player.getSize().x > SCREEN_WIDTH) {
            player.setPos(Vector2f(SCREEN_WIDTH - player.getSize().x, playerPos.y));
        }
        if(playerPos.y + player.getSize().y > SCREEN_HEIGHT) {
            player.setPos(Vector2f(playerPos.x, SCREEN_HEIGHT - player.getSize().y));
        }
        
        window.clear();
        window.draw(background);
        window.draw(player);
        window.draw(enemy);
        window.display();
    }

    return 0;
}