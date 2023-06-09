#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"
#include "../../include/core/InputHandler.h"

// Constructor for the PlayerInputComponent
PlayerInputComponent::PlayerInputComponent()
    : m_inputHandler(std::make_unique<PlayerInputHandler>())
{}

void PlayerInputComponent::update(Game& game)
{
    // 1. Get a shared_ptr to the player and set the player's velocity to 0, 0 at the start of the function
    std::shared_ptr<Player> player = game.getPlayer();
    auto v = player->getVelocityComp();
    v->setVelocity(0.0f, 0.0f);

    // 2. Retrieve the vector of commands
    std::vector<std::shared_ptr<Command>> commands = m_inputHandler->handleInput();

    // 3. Execute all commands received
    for (const auto& command : commands)
    {
        command->execute(game); // Pass the game object instead of the player object
    }
}
