#include "Timer.hpp"

Timer::Timer() 
    :mLastTime(0), mDeltaTime(0.0f), mStarted(false)
{}

void Timer::start() {
    mStarted = true;
    mLastTime = SDL_GetTicks();
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