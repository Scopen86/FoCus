#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "RenderWindow.hpp"
#include "defs.hpp"
#include "Entity.hpp"
#include "Logic.hpp"
#include "Player.hpp"

int main(int argc, char* argv[]) {
    RenderWindow window;
    bool gameRunning = true;
   
    SDL_Texture* backgroundTex = window.loadTexture("./res/background.jpg");
    SDL_Texture* playerTex = window.loadTexture("./res/player.png");
    SDL_Texture* enemyTex = window.loadTexture("./res/squareEnemy.png");

    Entity background(backgroundTex, Vector2f(0, 0), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    Player player(playerTex, Vector2f(30, SCREEN_HEIGHT / 2), 4.0f);

    std::ifstream enemiesFile("./res/enemiesPos.txt");
    std::vector<Entity> enemies;
    if(enemiesFile.is_open()) {
        int x, y, sizeX, sizeY;
        std::string line;
        while(enemiesFile >> x >> y >> sizeX >> sizeY) {
            Entity enemy(enemyTex, Vector2f(x, y), Vector2f(sizeX, sizeY));
            enemies.push_back(enemy);
        }
        enemiesFile.close();

    } else {
        std::cout << "Failed to open enemies file." << std::endl;
        return 1;
    }
    
    SDL_Event event;
    while(gameRunning) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }

        Logic logic;
        logic.handlePlayerMovement(player);
        if(logic.checkCollision(player, enemies)) {
            player.hit();
            float tempSpeed = player.getSpeed();
            player.setSpeed(0.0f);
            
            window.shake(-1);
            SDL_Delay(50);

            player.setSpeed(tempSpeed);

            std::cout << "Player HP: " << player.getHp() << std::endl;
            if(player.getHp() <= 0) {
                std::cout << "Game Over!" << std::endl;
                gameRunning = false;
            }
        }
        

        window.clear();
        window.draw(background);
        window.draw(player);
        for(Entity enemy : enemies) {window.draw(enemy);}
        window.display();
    }

    return 0;
}