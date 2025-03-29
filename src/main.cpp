#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "RenderWindow.hpp"
#include "defs.hpp"
#include "Entity.hpp"
#include "Logic.hpp"
#include "Player.hpp"
#include "Audio.hpp"

int main(int argc, char* argv[]) {
    RenderWindow window;
    bool gameRunning = true;

    Audio backgroundMusic;
    backgroundMusic.loadSound("./res/Chronos(cut).wav");
    backgroundMusic.playSound();
    Audio gameOverSound;
    gameOverSound.loadSound("./res/gameOver.wav");
   
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
            window.shake(-1);

            std::cout << "Player HP: " << player.getHp() << std::endl;
            if(player.getHp() <= 0) {
                gameOverSound.playSound();
                std::cout << "Game Over!" << std::endl;
                SDL_Delay(2000); 
                gameRunning = false;
            }
        }
        
        window.clear();
        
        window.draw(background);
        window.draw(player);
        for(Entity enemy : enemies) {
            window.draw(enemy);
        }
        window.drawText("HP: " + std::to_string(player.getHp()), Vector2f(10, 10), {255, 255, 255}, 24);
        float seconds = SDL_GetTicks() / 1000.0f;
        std::stringstream timeStream;
        timeStream << std::fixed << std::setprecision(2) << seconds;
        window.drawText("Time: " + timeStream.str() + "s", Vector2f(10, 40), {255, 255, 255}, 24);
        
        window.display();
    }

    return 0;
}