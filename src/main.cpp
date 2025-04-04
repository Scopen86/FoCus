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
   
    // SDL_Texture* backgroundTex = window.loadTexture("./res/background.png");

    SDL_Texture* frame0Tex = window.loadTexture("./res/frame0.png");
    SDL_Texture* frame1Tex = window.loadTexture("./res/frame1.png");
    SDL_Texture* frame2Tex = window.loadTexture("./res/frame2.png");
    SDL_Texture* frame3Tex = window.loadTexture("./res/frame3.png");

    Entity frame0(frame0Tex, Vector2f(40, 750), Vector2f(100, 100), 0.0f);
    Entity frame1(frame1Tex, Vector2f(140, 750), Vector2f(100, 100), 0.0f);
    Entity frame2(frame2Tex, Vector2f(240, 750), Vector2f(100, 100), 0.0f);
    Entity frame3(frame3Tex, Vector2f(340, 750), Vector2f(100, 100), 0.0f);

    SDL_Texture* frame0checkTex = window.loadTexture("./res/frame0check.png");
    SDL_Texture* frame1checkTex = window.loadTexture("./res/frame1check.png");
    SDL_Texture* frame2checkTex = window.loadTexture("./res/frame2check.png");
    SDL_Texture* frame3checkTex = window.loadTexture("./res/frame3check.png");

    Entity frame0check(frame0checkTex, Vector2f(40, 750), Vector2f(100, 100), 0.0f);
    Entity frame1check(frame1checkTex, Vector2f(140, 750), Vector2f(100, 100), 0.0f);
    Entity frame2check(frame2checkTex, Vector2f(240, 750), Vector2f(100, 100), 0.0f);
    Entity frame3check(frame3checkTex, Vector2f(340, 750), Vector2f(100, 100), 0.0f);

    SDL_Texture* target0Tex = window.loadTexture("./res/target0.png");
    SDL_Texture* target1Tex = window.loadTexture("./res/target1.png");
    SDL_Texture* target2Tex = window.loadTexture("./res/target2.png");
    SDL_Texture* target3Tex = window.loadTexture("./res/target3.png");

    // Entity background(backgroundTex, Vector2f(0, 0), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    std::ifstream targetTimings("./res/targetTimings.txt");
    std::vector<Entity> targets;
    if(targetTimings.is_open()) {
        int type;
        float timing;
        while(targetTimings >> type >> timing) {
            switch(type) {
                case 0: {
                    Entity target0(target0Tex, Vector2f(40, 0), Vector2f(100, 100), timing);
                    targets.push_back(target0);
                    break;
                }
                case 1: {
                    Entity target1(target1Tex, Vector2f(140, 0), Vector2f(100, 100), timing);
                    targets.push_back(target1);
                    break;
                }
                case 2: {
                    Entity target2(target2Tex, Vector2f(240, 0), Vector2f(100, 100), timing);
                    targets.push_back(target2);
                    break;
                }
                case 3: {
                    Entity target3(target3Tex, Vector2f(340, 0), Vector2f(100, 100), timing);
                    targets.push_back(target3);
                    break;
                }
                default: {
                    std::cout << "Invalid target type: " << type << std::endl;
                    break;
                }
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
        
        // Process events for quit and key up events only
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameRunning = false;
            }
            else if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    case SDLK_d: logic.setFrame0Active(false); break;
                    case SDLK_f: logic.setFrame1Active(false); break;
                    case SDLK_j: logic.setFrame2Active(false); break;
                    case SDLK_k: logic.setFrame3Active(false); break;
                }
            }
        }

        logic.handleKeyboardInput(frame0, frame1, frame2, frame3, targets, currentTime);

        window.clear();
        window.draw(frame0);
        window.draw(frame1);
        window.draw(frame2);
        window.draw(frame3);

        if(logic.isFrame0Active()) window.draw(frame0check);
        if(logic.isFrame1Active()) window.draw(frame1check);
        if(logic.isFrame2Active()) window.draw(frame2check);
        if(logic.isFrame3Active()) window.draw(frame3check);

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
        window.drawText(ss.str(), Vector2f(SCREEN_WIDTH / 2 - 50, 40), WHITE, 24);
        window.drawText("Score: " + std::to_string(static_cast<int>(logic.getScore())), Vector2f(SCREEN_WIDTH / 2 - 100, 80), WHITE, 24);
        
        window.display();
    }

    return 0;
}