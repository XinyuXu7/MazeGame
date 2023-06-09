#include "../../include/systems/Systems.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/entities/Entity.h"

TTLSystem::TTLSystem() {
    componentMask.turnOnBit(static_cast<int>(ComponentID::TTL));
}

void TTLSystem::update(Game* game, std::shared_ptr<Entity> entity, float elapsed) {
    std::shared_ptr<TTLComponent> ttlComponent = entity->getTTLComponent();

    if (!ttlComponent) {
        throw std::runtime_error("TTLSystem::update() called on an entity without a TTLComponent.");
    }

    ttlComponent->decreaseTTL();

    if (ttlComponent->getTTL() <= 0) {
        entity->deleteEntity();
    }
}
