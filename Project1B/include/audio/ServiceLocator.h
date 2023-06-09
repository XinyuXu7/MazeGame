#pragma once
#include "AudioService.h"

class ServiceLocator {
private:
    static AudioService* audioService;

public:
    static void provide(AudioService* service);
    static AudioService* getAudio();
};
