#include "Audio.hpp"

Audio::Audio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
    }
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
    return true;
}

void Audio::playSound() {
    if (soundChunk) {
        if (Mix_PlayChannel(-1, soundChunk, 0) == -1) {
            std::cout << "Failed to play sound: " << Mix_GetError() << std::endl;
        }
    }
}