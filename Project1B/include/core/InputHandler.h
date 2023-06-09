#pragma once
#include "Command.h"

class Command;

class GameInputHandler {
public:
    GameInputHandler();
    std::shared_ptr<Command> handleInput();

private:
    std::shared_ptr<Command> pauseCommand;
};

enum class InputMode { ASDW, ARROW_KEYS };

class PlayerInputHandler {
public:
    PlayerInputHandler();
    const std::vector<std::shared_ptr<Command>>& handleInput();

private:
    InputMode mode;
    std::vector<std::shared_ptr<Command>> commandVector;

    std::shared_ptr<Command> moveRightCommand;
    std::shared_ptr<Command> moveLeftCommand;
    std::shared_ptr<Command> moveUpCommand;
    std::shared_ptr<Command> moveDownCommand;
    std::shared_ptr<Command> attackCommand;
    std::shared_ptr<Command> shoutCommand;
};
