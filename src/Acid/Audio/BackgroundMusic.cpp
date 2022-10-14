#include "BackgroundMusic.h"

#include <stdexcept>

namespace acid 
{
    void BackgroundMusic::load(const std::string& filePath) 
    {
        if (_music.openFromFile(filePath) == false)
        {
            throw std::runtime_error("Cannot find background music file.");
        }

    }

    void BackgroundMusic::play() 
    {
        if (_music.getStatus() != _music.Playing) 
        {
            _music.play();
        }
    }

    void BackgroundMusic::pause() 
    {
        _music.pause();
    }

    void BackgroundMusic::stop() 
    {
        _music.stop();
    }

    bool BackgroundMusic::isPlaying() const
    {
        return _music.getStatus() == _music.Playing;
    }
}