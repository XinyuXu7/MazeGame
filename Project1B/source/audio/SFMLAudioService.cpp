#include "../../include/audio/SFMLAudioService.h"
#include <iostream>

SFMLAudioService::SFMLAudioService() {
    if (!buffer1.loadFromFile("audio/attack.flac")) {
        std::cerr << "Error: could not load sound file 'attack.flac'\n";
    }
    else {
        std::cout << "Successfully loaded sound file 'attack.flac'\n";
    }
    if (!buffer2.loadFromFile("audio/fire.wav")) {
        std::cerr << "Error: could not load sound file 'fire.wav'\n";
    }
    else {
        std::cout << "Successfully loaded sound file 'fire.wav'\n";
    }
    if (!buffer3.loadFromFile("audio/potion.flac")) {
        std::cerr << "Error: could not load sound file 'potion.flac'\n";
    }
    else {
        std::cout << "Successfully loaded sound file 'potion.flac'\n";
    }

    soundBuffers["attack"] = buffer1;
    soundBuffers["fire"] = buffer2;
    soundBuffers["potion"] = buffer3;
}

void SFMLAudioService::playSound(const std::string& sound) {
    if (soundBuffers.find(sound) == soundBuffers.end()) {
        std::cerr << "Error: no sound buffer found for sound " << sound << "\n";
        return;
    }
    this->sound.setBuffer(soundBuffers[sound]);
    this->sound.play();
}
