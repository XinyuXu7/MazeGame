#include "../../include/components/VelocityComponent.h"

// Constructor implementation
VelocityComponent::VelocityComponent(float speed) : speed(speed) {}

// Set velocity implementation
void VelocityComponent::setVelocity(float x, float y) {
    velocityDirection.x = x;
    velocityDirection.y = y;
}

// Get velocity implementation
const Vector2f& VelocityComponent::getVelocity() const {
    return velocityDirection;
}

// Update function definition (empty for now)
void VelocityComponent::update(Entity& entity, float elapsedTime) {
    // Calculate the movement based on the velocity direction, speed, and elapsed time
    Vector2f movement = velocityDirection * speed * elapsedTime;

    // Get the current position of the entity
    const Vector2f& currentPosition = entity.getPosition();

    // Update the position of the entity with the new movement
    entity.getPositionComponent().setPosition(currentPosition.x + movement.x, currentPosition.y + movement.y);
}
