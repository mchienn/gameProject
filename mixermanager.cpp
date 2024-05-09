#include "MixerManager.h"

MixerManager::MixerManager() {
    //init audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
       SDL_Log( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );
    }
}

MixerManager::~MixerManager() {
    //clean
    Mix_CloseAudio();
}

void MixerManager::playMusic(const char* filename) {
    Mix_Music *music = Mix_LoadMUS(filename);
    Mix_PlayMusic(music, -1);
}

void MixerManager::stopMusic() {
    Mix_VolumeMusic(0);
}

void MixerManager::continueMusic()
{
    Mix_ResumeMusic();
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void MixerManager::loadEffect(const char* filename)
{
    effect = Mix_LoadWAV(filename);
}

void MixerManager::playEffect() {
    Mix_PlayChannel(-1, effect, 0);
}

void MixerManager::effectOff()
{
    Mix_VolumeChunk(effect, 0);
}

void MixerManager::effectOn()
{
    Mix_VolumeChunk(effect, MIX_MAX_VOLUME);
}
