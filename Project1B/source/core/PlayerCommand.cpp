#include"../../include/core/Command.h"
#include"../../include/core/Game.h"
#include"../../include/entities/Player.h"
#include "../../include/audio/ServiceLocator.h"
#include "../../include/observer/AchievementSystem.h"


void MoveRightCommand::execute(Game& game) {
	auto player = game.getPlayer();
	auto velocity = player->getVelocityComp();
	velocity->setVelocity(1.0f, velocity->getVelocity().y);
}

void MoveLeftCommand::execute(Game& game) {
	auto player = game.getPlayer();
	auto velocity = player->getVelocityComp();
	velocity->setVelocity(-1.0f, velocity->getVelocity().y);
}

void MoveUpCommand::execute(Game& game) {
	auto player = game.getPlayer();
	auto velocity = player->getVelocityComp();
	velocity->setVelocity(velocity->getVelocity().x, -1.0f);
}

void MoveDownCommand::execute(Game& game) {
	auto player = game.getPlayer();
	auto velocity = player->getVelocityComp();
	velocity->setVelocity(velocity->getVelocity().x, 1.0f);
}

void AttackCommand::execute(Game& game)
{
	if (game.getPlayer()->isShouting()){
		game.getPlayer()->setShouting(false);
	}
	game.getPlayer()->setAttacking(true);
	ServiceLocator::getAudio()->playSound("attack");
}

void ShoutCommand::execute(Game& game)
{
	if (game.getPlayer()->isAttacking()){
		game.getPlayer()->setAttacking(false);
	}
	game.getPlayer()->setShouting(true);

	// Increment the shout count
	game.getPlayer()->incrementShoutCount();

	// Check if the player has shouted five times
	AchievementSystem::getInstance().notify(*game.getPlayer(), "Shout");
	
}