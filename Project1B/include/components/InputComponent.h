#pragma once

#include <memory> // For std::unique_ptr
#include "../components/Components.h" 

// Forward declarations to avoid circular dependencies
class Game;
class PlayerInputHandler;

class InputComponent : public Component // Derive from the Component interface
{
public:
    // Virtual destructor
    virtual ~InputComponent() {}

    // Pure virtual update function
    virtual void update(Game& game) = 0;

    // Implement the getID() function from the Component interface
    ComponentID getID() const override {
        return ComponentID::INPUT;
    }
};

class PlayerInputComponent : public InputComponent
{
public:
    // Default constructor
    PlayerInputComponent();

    // Override the update function from the base class
    void update(Game& game) override;

private:
    // Unique pointer to a PlayerInputHandler
    std::unique_ptr<PlayerInputHandler> m_inputHandler;
};
