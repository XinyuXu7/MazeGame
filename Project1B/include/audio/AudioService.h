#pragma once
#include <string>
#include <SFML/Audio.hpp>

class AudioService {
public:
    virtual ~AudioService() = default;
    virtual void playSound(const std::string& sound) = 0;
};
