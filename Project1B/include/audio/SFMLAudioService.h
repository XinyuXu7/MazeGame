#pragma once
#include "AudioService.h"
#include <map>

class SFMLAudioService : public AudioService {
private:
    sf::SoundBuffer buffer1, buffer2, buffer3;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    sf::Sound sound;

public:
    SFMLAudioService();
    void playSound(const std::string& sound) override;
};
