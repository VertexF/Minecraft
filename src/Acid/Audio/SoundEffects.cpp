#include "SoundEffects.h"

#include <stdexcept>

namespace acid 
{
    void SoundEffects::load(const std::string& filePath, bool isOverPlayable, bool loop)
    {
        //TODO: fix this functions arguements when you have more time to thing.
        _isOverPlayable = isOverPlayable;

        if (_buffer.loadFromFile(filePath) == false) 
        {
            throw std::runtime_error("Could not load sound effect file.");
        }

        _sound.setBuffer(_buffer);
        _sound.setLoop(loop);
    }

    void SoundEffects::play() 
    {
        if (_isOverPlayable)
        {
            _sound.play();
        }
        else
        {
            if (_sound.getStatus() != _sound.Playing)
            {
                _sound.play();
            }
        }
    }

    void SoundEffects::stop()
    {
        _sound.stop();
    }

    void SoundEffects::pause() 
    {
        _sound.pause();
    }

    void SoundEffects::setVolume(float volume)
    {
        _sound.setVolume(volume);
    }
}