#include "../../include/entities/Fire.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE)
{
    ttl = std::make_shared<TTLComponent>(startTimeToLive);
    addComponent(ttl);

    velocity = std::make_shared<VelocityComponent>(10);
    addComponent(velocity);

    inUse = false;
}

Fire::~Fire()
{}

void Fire::update(Game* game, float elapsed)
{
    Entity::update(game, elapsed);
    velocity->update(*this, elapsed);
}

std::shared_ptr<TTLComponent> Fire::getTTLComponent()
{
    return ttl; // Return the TTLComponent shared pointer for the Fire class
}