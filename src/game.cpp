#include <SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Game.hpp"
#include "defs.hpp"

Game::Game() : gameRunning(false) {}

Game::~Game() {
    for(SDL_Texture* tex : frameTex) {
        SDL_DestroyTexture(tex);
    }
    
    for(SDL_Texture* tex : frameCheckTex) {
        SDL_DestroyTexture(tex);
    }
    
    for(SDL_Texture* tex : targetTex) {
        SDL_DestroyTexture(tex);
    }
}

bool Game::init() {
    gameRunning = true;
    gameTimer.start();
    
    if (!loadResources()) {
        std::cout << "Failed to load resources. Stopping" << std::endl;
        return false;
    }

    if(!loadTargets()) {
        std::cout << "Failed to load targets. Stopping" << std::endl;
        return false;
    }
    
    for (int i = 0; i < 4; i++) {
        float xPos = 40 + (i * 100);
        frames.push_back(Entity(frameTex[i], Vector2f(xPos, DEFAULT_Y_POS)));
        frameChecks.push_back(Entity(frameCheckTex[i], Vector2f(xPos, DEFAULT_Y_POS)));
    }
    
    return true;
}

void Game::run() {
    backgroundMusic.playSound();

    while(gameRunning) {
        gameTimer.update();
        float deltaTime = gameTimer.getDeltaTime();
        float currentTime = gameTimer.getTime();
        
        handleEvents();
        update(deltaTime, currentTime);
        render(currentTime);
    }
}

void Game::handleEvents() {
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            gameRunning = false;
        }
        else {
            logic.processKeyEvent(event);
        }
    }
}

void Game::update(float deltaTime, float currentTime) {
    logic.handleInput(frames, targets, currentTime);
    
    for(Entity& target : targets) {
        if(currentTime >= target.getTiming() && 
           target.getPosition().y >= 0 && 
           target.getPosition().y < SCREEN_HEIGHT) {
            target.update(deltaTime);
        }
    }
}

void Game::render(float currentTime) {
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
        }
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << (currentTime / 190 * 100.0) << "%";
    window.drawText(ss.str(), Vector2f(SCREEN_WIDTH / 2 - 30, 40), WHITE, 24);
    window.drawText("Score: " + std::to_string(static_cast<int>(logic.getScore())), 
                   Vector2f(SCREEN_WIDTH / 2 - 100, 80), WHITE, 24);
    
    window.display();
}

bool Game::loadResources() {
    frameTex = {
        window.loadTexture("./res/textures/frame0.png"),
        window.loadTexture("./res/textures/frame1.png"),
        window.loadTexture("./res/textures/frame2.png"),
        window.loadTexture("./res/textures/frame3.png")
    };
    
    frameCheckTex = {
        window.loadTexture("./res/textures/frame0check.png"),
        window.loadTexture("./res/textures/frame1check.png"),
        window.loadTexture("./res/textures/frame2check.png"),
        window.loadTexture("./res/textures/frame3check.png")
    };
    
    targetTex = {
        window.loadTexture("./res/textures/target0.png"),
        window.loadTexture("./res/textures/target1.png"),
        window.loadTexture("./res/textures/target2.png"),
        window.loadTexture("./res/textures/target3.png")
    };
    
    backgroundMusic.loadSound("./res/level/NH22_Isolation_Limbo_Remix.wav");
    
    return true;
}

bool Game::loadTargets() {
    std::ifstream targetTimings("./res/level/targetTimings.txt");
    
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
        return true;
    } else {
        std::cout << "Failed to open ./res/level/targetTimings.txt file." << std::endl;
        return false;
    }
}