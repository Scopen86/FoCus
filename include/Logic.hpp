#pragma once
#include <vector>
#include <SDL.h>
#include "Entity.hpp"

class Logic {
    public:
        Logic();
        
        bool checkCollision(Entity& frame, Entity& target);
        void calculateScore(Entity& frame, Entity& target);
        
        void handleKeyboardInput(Entity& frame0, Entity& frame1, Entity& frame2, Entity& frame3,
                               std::vector<Entity>& targets, float currentTime);
        
        bool isFrame0Active() const { return frame0Active; }
        bool isFrame1Active() const { return frame1Active; }
        bool isFrame2Active() const { return frame2Active; }
        bool isFrame3Active() const { return frame3Active; }
        
        void setFrame0Active(bool active) { frame0Active = active; }
        void setFrame1Active(bool active) { frame1Active = active; }
        void setFrame2Active(bool active) { frame2Active = active; }
        void setFrame3Active(bool active) { frame3Active = active; }
        
        double getScore() const { return score; }
    
    private:
        double score = 0.0;
        bool frame0Active = false;
        bool frame1Active = false;
        bool frame2Active = false;
        bool frame3Active = false;
};