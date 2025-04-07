#include <cmath>

#include "Timer.hpp"

Timer::Timer() 
    :mLastTime(0), mDeltaTime(0.0f), mStarted(false), mStartTime(0)
{}

void Timer::start() {
    mStarted = true;
    mStartTime = SDL_GetTicks();
    mLastTime = mStartTime;
    mDeltaTime = 0.0f;
}

void Timer::stop() {
    mStarted = false;
}

void Timer::update() {
    if (!mStarted) return;
    
    Uint32 currentTime = SDL_GetTicks();
    mDeltaTime = (currentTime - mLastTime) / 1000.0f;
    
    mLastTime = currentTime;
}

float Timer::getTime() {
    if (!mStarted) return 0.0f;
    
    // Calculate elapsed time since timer was STARTED
    float seconds = (SDL_GetTicks() - mStartTime) / 1000.0f;
    return seconds;
}
