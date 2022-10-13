#ifndef BACKGROUND_MUSIC_HDR
#define BACKGROUND_MUSIC_HDR

#include <string>

#include <SFML/Audio.hpp>

namespace acid 
{
    class BackgroundMusic 
    {
    public:
        void load(const std::string& filePath);

        void play();
        void pause();
        void stop();
        bool isPlaying() const;
    private:
        sf::Music _music;
    };
}

#endif // !BACKGROUND_MUSIC_HDR
