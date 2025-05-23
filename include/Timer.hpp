#pragma once
#include <SDL.h>

class Timer {
public:
    Timer();
    
    void start();
    void stop();
    void update();

    float getTime();
    float getDeltaTime() const { return mDeltaTime; }
    
private:
    Uint32 mStartTime;
    Uint32 mLastTime;
    float mDeltaTime;
    bool mStarted;
};