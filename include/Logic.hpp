#pragma once
#include <vector>
#include <SDL.h>
#include <string>

#include "Entity.hpp"

class Logic {
    public:
        Logic();
        
        bool checkCollision(Entity& frame, Entity& target);
        void calculateScore(Entity& frame, Entity& target);
        
        void handleInput(std::vector<Entity>& frames, std::vector<Entity>& targets, float currentTime);
        void processKeyEvent(const SDL_Event& event);
        
        bool isFrameActive(int frameIndex) const;
        double getScore() const { return score; }
        void resetScore() { 
            score = 0.0f; 
            combo = 0; 
            maxCombo = 0; 
            resetGradeCounts();
        }
        
        
        int getCombo() const { return combo; }
        int getMaxCombo() const { return maxCombo; }
        int getLastHitGrade() const { return lastHitGrade; }
        const std::string getGradeString() const;
        
        int getPerfectCount() const { return perfectCount; }
        int getGreatCount() const { return greatCount; }
        int getGoodCount() const { return goodCount; }
        int getOkayCount() const { return okayCount; }
        int getMissCount() const { return missCount; }
        
        void checkMissedTargets(std::vector<Entity>& targets, float currentTime);
        
    private:
        double score = 0.0;
        std::vector<bool> frameActive;
        std::vector<SDL_Scancode> keyScanCodes;
        
        int combo = 0;
        int maxCombo = 0;
        int lastHitGrade = 0; // 0: MISS, 1: OKAY, 2: GOOD, 3: GREAT, 4: PERFECT
        
        int perfectCount = 0;
        int greatCount = 0;
        int goodCount = 0;
        int okayCount = 0;
        int missCount = 0;
        
        void incrementCombo() { combo++; maxCombo = std::max(maxCombo, combo); }
        void resetCombo() { combo = 0; }
        void resetGradeCounts() { perfectCount = 0; greatCount = 0; goodCount = 0; okayCount = 0; missCount = 0; }
};