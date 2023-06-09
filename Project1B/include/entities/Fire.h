#pragma once
#include "Entity.h"
#include "../components/TTLComponent.h"
#include "../components/VelocityComponent.h"
#include <memory>

class Fire : public Entity
{
public:
    const int startTimeToLive = 150; //frames

    Fire();
    ~Fire();

    virtual void update(Game* game, float elapsed = 1.0f) override;
    std::shared_ptr<VelocityComponent> getVelocityComp() const { return velocity; }

    virtual std::shared_ptr<TTLComponent> getTTLComponent() override;

    //pool
    void setInUse(bool value) { inUse = value; }
    bool isInUse() const { return inUse; }

private:

    std::shared_ptr<TTLComponent> ttl;
    std::shared_ptr<VelocityComponent> velocity;
    bool inUse;
};


