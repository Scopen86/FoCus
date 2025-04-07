#pragma once
#include <SDL_mixer.h>
#include <iostream>

class Audio {
    public:
        Audio();
        ~Audio();
        
        bool loadSound(const char* path);
        void playSound();
        void stopSound();
    private:
        Mix_Chunk* soundChunk = nullptr;
};