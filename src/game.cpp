#include <SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Game.hpp"
#include "defs.hpp"

Game::Game() 
    :gameRunning(false), userQuit(false) {};

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

bool Game::run() {
    gameTimer.start();
    backgroundMusic.playSound();

    while(gameRunning) {
        gameTimer.update();
        float deltaTime = gameTimer.getDeltaTime();
        float currentTime = gameTimer.getTime();
        
        handleEvents();
        update(deltaTime, currentTime);
        render(currentTime);
    }

    return gameRunning;
}

void Game::handleEvents() {
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            gameRunning = false;
            userQuit = true;
        }
        else {
            logic.processKeyEvent(event);
        }
    }
}

void Game::update(float deltaTime, float currentTime) {
    logic.handleInput(frames, targets, currentTime);
    logic.checkMissedTargets(targets, currentTime);
    
    for(Entity& target : targets) {
        if(currentTime >= target.getTiming() && 
           target.getPosition().y >= 0 && 
           target.getPosition().y < SCREEN_HEIGHT) {
            target.update(deltaTime);
        }
    }

    percentage = (currentTime / 200) * 100.0f;
    if(percentage >= 100.0f) {
        gameRunning = false;
    }

    score = logic.getScore();
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
    ss << std::fixed << std::setprecision(2) << (percentage) << "%";
    window.drawText(ss.str(), Vector2f(SCREEN_WIDTH / 2 - 30, 40), WHITE, 24);
    window.drawText("Score: " + std::to_string(score), 
                   Vector2f(SCREEN_WIDTH / 2 - 100, 80), WHITE, 24);
    
    SDL_Color gradeColor = WHITE;
    switch (logic.getLastHitGrade()) {
        case 4: gradeColor = {255, 215, 0, 255}; break;  // Gold
        case 3: gradeColor = {0, 255, 0, 255};   break;  // Green
        case 2: gradeColor = {0, 191, 255, 255}; break;  // Blue
        case 1: gradeColor = {255, 165, 0, 255}; break;  // Orange
        case 0: gradeColor = {255, 0, 0, 255};   break;  // Red
    }
    
    if(logic.getCombo() > 0) {
        window.drawText(logic.getGradeString() + " X" + std::to_string(logic.getCombo()), 
                        Vector2f(SCREEN_WIDTH / 2 - 50, 120), gradeColor, 30);
    }
    else {
        window.drawText(logic.getGradeString(), Vector2f(SCREEN_WIDTH / 2 - 50, 120), gradeColor, 30);
    }
    
    window.display();
}

bool Game::loadResources() {
    frameTex = {
        window.loadTexture("./res/textures/game/frame0.png"),
        window.loadTexture("./res/textures/game/frame1.png"),
        window.loadTexture("./res/textures/game/frame2.png"),
        window.loadTexture("./res/textures/game/frame3.png")
    };
    
    frameCheckTex = {
        window.loadTexture("./res/textures/game/frame0check.png"),
        window.loadTexture("./res/textures/game/frame1check.png"),
        window.loadTexture("./res/textures/game/frame2check.png"),
        window.loadTexture("./res/textures/game/frame3check.png")
    };
    
    targetTex = {
        window.loadTexture("./res/textures/game/target0.png"),
        window.loadTexture("./res/textures/game/target1.png"),
        window.loadTexture("./res/textures/game/target2.png"),
        window.loadTexture("./res/textures/game/target3.png")
    };
    
    backgroundMusic.loadSound("./res/level/NH22_Isolation_Limbo_Remix.wav");
    
    return true;
}

bool Game::loadTargets() {
    const float delta = 1.5f; //The time it takes for the target to fall to the frames
    std::ifstream targetTimings("./res/level/targetTimings.txt");
    
    if(targetTimings.is_open()) {
        int type;
        float timing;
        while(targetTimings >> type >> timing) {
            if(type >= 0 && type < 4) {
                float xPos = 40 + (type * 100);
                targets.push_back(Entity(targetTex[type], Vector2f(xPos, 0), timing - delta));
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

void Game::reset() {
    gameRunning = true;
    gameTimer.stop();
    
    backgroundMusic.stopSound();
    
    targets.clear();
    loadTargets();
    
    logic.resetScore();
    
    percentage = 0.0f;
    score = 0;
}