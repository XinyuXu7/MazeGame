#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/Vector2.h"
#include "../components/Components.h"

class PositionComponent : public Component // Derive from the Component interface
{
public:
    // Constructor
    PositionComponent() : position(0.0f, 0.0f) {}

    // Getter for the position
    const Vector2f& getPosition() const { return position; }

    // Setter for the position
    void setPosition(float x, float y) { position.x = x; position.y = y; }

    // Implement the getID() function from the Component interface
    ComponentID getID() const override {
        return ComponentID::POSITION;
    }

private:
    Vector2f position;
};
