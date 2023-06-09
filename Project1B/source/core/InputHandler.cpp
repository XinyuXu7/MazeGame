#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <SFML/Window/Keyboard.hpp>
#include "../../include/audio/ServiceLocator.h"

GameInputHandler::GameInputHandler()
{
    pauseCommand = std::make_shared<PauseCommand>();
}

std::shared_ptr<Command> GameInputHandler::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        return pauseCommand;
    }
    return nullptr;
}


PlayerInputHandler::PlayerInputHandler()
{
    moveRightCommand = std::make_shared<MoveRightCommand>();
    moveLeftCommand = std::make_shared<MoveLeftCommand>();
    moveUpCommand = std::make_shared<MoveUpCommand>();
    moveDownCommand = std::make_shared<MoveDownCommand>();
    attackCommand = std::make_shared<AttackCommand>();
    shoutCommand = std::make_shared<ShoutCommand>();
}

const std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handleInput()
{
    // Switch input mode when Enter is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        mode = (mode == InputMode::ASDW) ? InputMode::ARROW_KEYS : InputMode::ASDW;
    }

    commandVector.clear();

    if (mode == InputMode::ASDW)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            commandVector.push_back(moveRightCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            commandVector.push_back(moveLeftCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            commandVector.push_back(moveUpCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            commandVector.push_back(moveDownCommand);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            commandVector.push_back(attackCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            commandVector.push_back(shoutCommand);
        }
    }
    else if (mode == InputMode::ARROW_KEYS)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            commandVector.push_back(moveRightCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            commandVector.push_back(moveLeftCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            commandVector.push_back(moveUpCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            commandVector.push_back(moveDownCommand);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            commandVector.push_back(attackCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            commandVector.push_back(shoutCommand);
        }
    }

    return commandVector;
}