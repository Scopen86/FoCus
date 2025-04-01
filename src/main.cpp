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
#include "Audio.hpp"
#include "Timer.hpp"

int main(int argc, char* argv[]) {
    RenderWindow window;
    bool gameRunning = true;

    Timer gameTimer;
    gameTimer.start();
    
    // Audio backgroundMusic;
    // backgroundMusic.loadSound("./res/Chronos(cut).wav");
    // backgroundMusic.playSound();
    // Audio gameOverSound;
    // gameOverSound.loadSound("./res/gameOver.wav");
   
    SDL_Texture* backgroundTex = window.loadTexture("./res/background.png");
    SDL_Texture* triangleFrameTex = window.loadTexture("./res/triangleFrame.png");
    SDL_Texture* triangleTex = window.loadTexture("./res/triangle.png");

    // Entity background(backgroundTex, Vector2f(0, 0), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    Entity triangleFrame(triangleFrameTex, Vector2f(200, 600), Vector2f(32, 32));
    Entity triangle(triangleTex, Vector2f(200, 10), Vector2f(28, 28), 100.0f);

    std::ifstream targetTimings("./res/frameTiming.txt");
    std::vector<Entity> targets;
    if(targetTimings.is_open()) {
        int type;
        float timing;
        while(targetTimings >> type >> timing) {
            switch(type) {
                case 0:
                    break;
                case 1:
                    break;
                case 2: {
                    Entity target(triangleTex, Vector2f(200, 10), Vector2f(28, 28), timing);
                    targets.push_back(target);
                    break;
                }
                case 3:
                    break;
                default:
                    break;
            }  
        }
        targetTimings.close();

    } else {
        std::cout << "Failed to open ./res/frameTiming.txt file." << std::endl;
        return 1;
    }
    
    SDL_Event event;
    while(gameRunning) {
        // Update delta time at the beginning of each frame
        gameTimer.update();
        float deltaTime = gameTimer.getDeltaTime();
        float currentTime = gameTimer.getTime();
        
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }

        window.clear();
        
        // window.draw(background);
        window.draw(triangleFrame);
        window.draw(triangle);

        triangle.update(deltaTime);
        
        for(Entity& target : targets) {
            window.draw(target);
            target.update(deltaTime);
        }
        
        // window.drawText("HP: " + std::to_string(player.getHp()), Vector2f(10, 10), WHITE, 24);
        window.drawText("Time: " + std::to_string(currentTime) + "s", Vector2f(10, 40), {255, 255, 255, 255}, 24);
        
        window.display();

        // Logic logic;
        // logic.handlePlayerMovement(player, deltaTime);
        // if(logic.checkCollision(player, enemies)) {
        //     player.hit();
        //     window.shake(-1);

        //     std::cout << "Player HP: " << player.getHp() << std::endl;
        //     if(player.getHp() <= 0) {
        //         gameOverSound.playSound();
        //         std::cout << "Game Over!" << std::endl;
        //         SDL_Delay(2000); 
        //         gameRunning = false;
        //     }
        // }
    }

    return 0;
}