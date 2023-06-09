#include "../../include/audio/ServiceLocator.h"

AudioService* ServiceLocator::audioService = nullptr;

void ServiceLocator::provide(AudioService* service) {
    audioService = service;
}

AudioService* ServiceLocator::getAudio() {
    return audioService;
}
