#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Logic.hpp"
#include "Audio.hpp"
#include "Timer.hpp"

class Game {
public:
    Game();
    ~Game();
    
    bool init();
    bool run();

    void quit() { gameRunning = false; }
    RenderWindow& getWindow() { return window; }
    int getScore() const { return score; }
    void reset();
    bool didUserQuit() const { return userQuit; }
    int getMaxCombo() const { return logic.getMaxCombo(); }
private:
    void handleEvents();
    void update(float deltaTime, float currentTime);
    void render(float currentTime);
    bool loadResources();
    bool loadTargets();
    
    RenderWindow window;
    bool gameRunning;
    int score;
    Timer gameTimer;
    Audio backgroundMusic;
    Logic logic;
    
    std::vector<SDL_Texture*> frameTex;
    std::vector<SDL_Texture*> frameCheckTex;
    std::vector<SDL_Texture*> targetTex;
    
    std::vector<Entity> frames;
    std::vector<Entity> frameChecks;
    std::vector<Entity> targets;
    
    SDL_Event event;
    float percentage;
    bool userQuit = false;
};