#pragma once
#include "../core/Game.h"
#include "../entities/Entity.h"
#include "../utils/Bitmask.h"

class System
{
public:
    virtual void update(Game* game, std::shared_ptr<Entity> entity, float elapsed) = 0;

    bool validate(std::shared_ptr<Entity> entity) const
    {
        return entity->hasComponent(componentMask);
    }

protected:
    Bitmask componentMask;
};

class TTLSystem : public System
{
public:
    TTLSystem();
    virtual void update(Game* game, std::shared_ptr<Entity> entity, float elapsed) override;
};