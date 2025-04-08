#include "Audio.hpp"

Audio::Audio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
    }
    
    defaultVolume = MIX_MAX_VOLUME / 4;
}

Audio::~Audio() {
    Mix_FreeChunk(soundChunk);
    Mix_CloseAudio();
}

bool Audio::loadSound(const char* path) {
    soundChunk = Mix_LoadWAV(path);
    if (!soundChunk) {
        std::cout << "Failed to load sound: " << Mix_GetError() << std::endl;
        return false;
    }
    
    Mix_VolumeChunk(soundChunk, defaultVolume);
    return true;
}

void Audio::playSound() {
    if (soundChunk) {
        if (Mix_PlayChannel(-1, soundChunk, 0) == -1) {
            std::cout << "Failed to play sound: " << Mix_GetError() << std::endl;
        }
    }
}

void Audio::stopSound() {
    if (Mix_Playing(-1)) {
        Mix_HaltChannel(-1);
    }
}