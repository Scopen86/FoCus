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
    
    Audio backgroundMusic;
    backgroundMusic.loadSound("./res/NH22_Isolation_Limbo_Remix.wav");
    backgroundMusic.playSound();
   
    std::vector<SDL_Texture*> frameTex = {
        window.loadTexture("./res/frame0.png"),
        window.loadTexture("./res/frame1.png"),
        window.loadTexture("./res/frame2.png"),
        window.loadTexture("./res/frame3.png")
    };
    
    std::vector<SDL_Texture*> frameCheckTex = {
        window.loadTexture("./res/frame0check.png"),
        window.loadTexture("./res/frame1check.png"),
        window.loadTexture("./res/frame2check.png"),
        window.loadTexture("./res/frame3check.png")
    };
    
    std::vector<SDL_Texture*> targetTex = {
        window.loadTexture("./res/target0.png"),
        window.loadTexture("./res/target1.png"),
        window.loadTexture("./res/target2.png"),
        window.loadTexture("./res/target3.png")
    };
    
    std::vector<Entity> frames;
    std::vector<Entity> frameChecks;
    
    for (int i = 0; i < 4; i++) {
        float xPos = 40 + (i * 100);
        frames.push_back(Entity(frameTex[i], Vector2f(xPos, DEFAULT_Y_POS)));
        frameChecks.push_back(Entity(frameCheckTex[i], Vector2f(xPos, DEFAULT_Y_POS)));
    }

    std::vector<Entity> targets;
    std::ifstream targetTimings("./res/targetTimings.txt");
    
    if(targetTimings.is_open()) {
        int type;
        float timing;
        while(targetTimings >> type >> timing) {
            if(type >= 0 && type < 4) {
                float xPos = 40 + (type * 100);
                targets.push_back(Entity(targetTex[type], Vector2f(xPos, 0), timing));
            } else {
                std::cout << "Invalid target type: " << type << std::endl;
            }
        }
        targetTimings.close();
    } else {
        std::cout << "Failed to open ./res/targetTimings.txt file." << std::endl;
        return 1;
    }
    
    Logic logic;
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
            else {
                logic.processKeyEvent(event);
            }
        }

        logic.handleMovement(frames, targets, currentTime);

        window.clear();
        
        for(int i = 0; i < 4; i++) {
            window.draw(frames[i]);
            if(logic.isFrameActive(i)) {
                window.draw(frameChecks[i]);
            }
        }

        for(Entity& target : targets) {
            if(currentTime >= target.getTiming() && 
               target.getPosition().y >= 0 && 
               target.getPosition().y < SCREEN_HEIGHT) {
                    window.draw(target);
                    target.update(deltaTime);
            }
        }

        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << (currentTime / 209 * 100.0) << "%";
        window.drawText(ss.str(), Vector2f(SCREEN_WIDTH / 2 - 40, 40), WHITE, 24);
        window.drawText("Score: " + std::to_string(static_cast<int>(logic.getScore())), Vector2f(SCREEN_WIDTH / 2 - 100, 80), WHITE, 24);
        
        window.display();
    }
    
    return 0;
}