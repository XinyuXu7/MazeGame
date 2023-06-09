#pragma once

#include "../components/Components.h"

class HealthComponent : public Component // Derive from the Component interface
{
public:
    HealthComponent(int initHp, int maxHp) : currentHealth(initHp), maxHealth(maxHp) {}
    ~HealthComponent() {}

    int getHealth() { return currentHealth; }

    void changeHealth(int value) {
        currentHealth += value;
        if (currentHealth > maxHealth)
            currentHealth = maxHealth;
        if (currentHealth < 0)
            currentHealth = 0;
    }

    // Implement the getID() function from the Component interface
    ComponentID getID() const override {
        return ComponentID::HEALTH;
    }

protected:
    int currentHealth;
    int maxHealth;
};
