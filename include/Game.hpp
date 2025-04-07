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
    void run();

    void quit() { gameRunning = false; }
    RenderWindow& getWindow() { return window; }
    
private:
    void handleEvents();
    void update(float deltaTime, float currentTime);
    void render(float currentTime);
    bool loadResources();
    bool loadTargets();
    
    RenderWindow window;
    bool gameRunning;
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
};