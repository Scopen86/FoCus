#pragma once
#include <vector>
#include <SDL.h>
#include "Entity.hpp"

class Logic {
    public:
        Logic();
        
        bool checkCollision(Entity& frame, Entity& target);
        void calculateScore(Entity& frame, Entity& target);
        
        void handleMovement(std::vector<Entity>& frames, std::vector<Entity>& targets, float currentTime);
        void processKeyEvent(const SDL_Event& event);
        
        bool isFrameActive(int frameIndex) const;
        double getScore() const { return score; }
    
    private:
        double score = 0.0;
        std::vector<bool> frameActive;
        std::vector<SDL_Scancode> keyScanCodes;
};