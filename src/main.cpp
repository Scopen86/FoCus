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
#include "Timer.hpp"


int main(int argc, char* argv[]) {
    RenderWindow window;
    bool gameRunning = true;

    Timer gameTimer;
    gameTimer.start();

    Audio backgroundMusic;
    backgroundMusic.loadSound("./res/Chronos(cut).wav");
    backgroundMusic.playSound();
    Audio gameOverSound;
    gameOverSound.loadSound("./res/gameOver.wav");
   
    SDL_Texture* backgroundTex = window.loadTexture("./res/background.jpg");
    SDL_Texture* playerTex = window.loadTexture("./res/player.png");
    SDL_Texture* enemyTex = window.loadTexture("./res/squareEnemy.png");

    Entity background(backgroundTex, Vector2f(0, 0), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    Player player(playerTex, Vector2f(30, SCREEN_HEIGHT / 2), 3);

    std::ifstream enemiesFile("./res/enemiesPos.txt");
    std::vector<Entity> enemies;
    if(enemiesFile.is_open()) {
        int x, y, sizeX, sizeY;
        float vecX, vecY;
        std::string line;
        while(enemiesFile >> x >> y >> sizeX >> sizeY >> vecX >> vecY) {
            Entity enemy(enemyTex, Vector2f(x, y), Vector2f(sizeX, sizeY), Vector2f(vecX, vecY));
            enemies.push_back(enemy);
        }
        enemiesFile.close();

    } else {
        std::cout << "Failed to open enemies file." << std::endl;
        return 1;
    }
    
    SDL_Event event;
    while(gameRunning) {
        // Update delta time at the beginning of each frame
        gameTimer.update();
        float deltaTime = gameTimer.getDeltaTime();
        
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }

        window.clear();
        
        window.draw(background);
        window.draw(player);
        for(Entity& enemy : enemies) {
            window.draw(enemy);
        }
        window.drawText("HP: " + std::to_string(player.getHp()), Vector2f(10, 10), WHITE, 24);
        float seconds = SDL_GetTicks() / 1000.0f;
        std::stringstream timeStream;
        timeStream << std::fixed << std::setprecision(2) << seconds;
        window.drawText("Time: " + timeStream.str() + "s", Vector2f(10, 40), WHITE, 24);
        
        window.display();

        for(Entity& enemy : enemies) {
            enemy.update(deltaTime);
        }

        Logic logic;
        logic.handlePlayerMovement(player, deltaTime);
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
        
        
    }

    return 0;
}