// MixerManager.h
#ifndef MIXER_MANAGER_H
#define MIXER_MANAGER_H

#include <SDL_mixer.h>
#include <SDL.h>

class MixerManager
{
public:
    MixerManager();
    ~MixerManager();

    void playMusic(const char *filename);
    void stopMusic();
    void continueMusic();
    void playEffect();
    void loadEffect(const char *filename);
    void effectOff();
    void effectOn();

private:
    Mix_Chunk *effect;
};

#endif // MIXER_MANAGER_H
