#pragma once

#include "../components/Components.h"
#include "../utils/Vector2.h"
#include "../entities/Entity.h"

class VelocityComponent : public Component // Derive from the Component interface
{
public:
    // Constructor with default argument for speed
    explicit VelocityComponent(float speed = 1.f);

    // Member functions for setting the velocity and getting a reference to the velocity vector
    void setVelocity(float x, float y);
    const Vector2f& getVelocity() const;

    // Update function declaration
    void update(Entity& entity, float elapsedTime);

    // Implement the getID() function from the Component interface
    ComponentID getID() const override {
        return ComponentID::VELOCITY;
    }

private:
    // Member variables for velocity direction and speed
    Vector2f velocityDirection;
    float speed;
};
