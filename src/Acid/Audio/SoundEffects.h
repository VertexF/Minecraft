#ifndef SOUND_EFFECTS_HDR
#define SOUND_EFFECTS_HDR

#include <string>

#include <SFML/Audio.hpp>

namespace acid 
{
    class SoundEffects 
    {
    public:
        void load(const std::string& filePath, bool isOverPlayable, bool loop);

        void play();
        void stop();
        void pause();
        void setVolume(float volume);
    private:
        sf::Sound _sound;
        sf::SoundBuffer _buffer;

        bool _isOverPlayable;
    };
}

#endif // !SOUND_EFFECTS_HDR
