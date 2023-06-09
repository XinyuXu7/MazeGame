#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/InputComponent.h"
#include <iostream>
#include "../../include/audio/ServiceLocator.h"
#include "../../include/observer/AchievementSystem.h"




Player::Player() : Entity(EntityType::PLAYER), attacking(false), shouting(false), wood(0), shootCooldown(0), potionCount(0), shoutCount(0)
{
	//speed = playerSpeed;

	// VI.B: Create the unique pointer to the PlayerInputHandler object
	//inputHandler = std::make_unique<PlayerInputHandler>();
	// Initialize the unique pointer to a PlayerInputComponent object
	input = std::make_shared<PlayerInputComponent>();

	// Create the shared pointer to the HealthComponent object using startingHealth and maxHealth
	health = std::make_shared<HealthComponent>(startingHealth, maxHealth);

	// Initialize the shared pointer of VelocityComponent with playerSpeed:
	velocity = std::make_shared<VelocityComponent>(playerSpeed);

	// Initialize fire pool 
	firePool = std::make_shared<FirePool>(20);
}


Player::~Player() {}

void Player::update(Game* game, float elapsed)
{
	velocity->update(*this, elapsed);
		// VI.G Modify the code below to add the functionality to play the appropriate animations 
		//      and set the appropriate directions for movement depending on the  value of the
		//      velocity vector for moving up, down and left.
	bool isWalking = false;
	if (velocity->getVelocity().x > 0)
	{
		isWalking = true;
		spriteSheet.setSpriteDirection(Direction::Right);
	}
	else if (velocity->getVelocity().x < 0)
	{
		isWalking = true;
		spriteSheet.setSpriteDirection(Direction::Left);
	}
	else if (velocity->getVelocity().y != 0.0f)
	{
		isWalking = true;
	}

		// VI.F (1/2) If the X component of the velocity vector is positive, we're moving to the right.
		//            Set the animation of the spritesheet to "Walk". Mind the parameters required for the
		//			  animation: if it should start playing and if it should loop.
		//			  Additionally, you must also set the sprite direction (to Direction::Right) of the spritesheet.


		// VI.F (2/2) If the player is not moving, we must get back to playing the "Idle" animation.
	if (isAttacking())
	{
		spriteSheet.setAnimation("Attack", true, false);
	}
	else if (isShouting())
	{
		spriteSheet.setAnimation("Shout", true, false);
	}
	else if (isWalking)
	{
		spriteSheet.setAnimation("Walk", true, true);
	}
	else
	{
		spriteSheet.setAnimation("Idle", true, true);
	}

	
	// IV.D (1/2) Call the function update in the base class to do the general update stuff that is common to all entities.
	Entity::update(game, elapsed);

	// XI.B (2/2):  Reduce the shoot cooldown counter by the elapsed time at every frame. 
	//              Only do this if shoot cooldown is > 0 (can you guess why?)
	if (shootCooldown > 0) {
		shootCooldown -= elapsed;
	}

	// XI.A: Create an Fire entity object (using Player::createFire()) and add it to the game (using Game::addEntity).
	//       Then, remove the shooting cost (Player::shootingCost) from the wood member variable of this class
	//       Finally, wrap the functionality below in an IF statement, so we only spawn fire when:
	//            1) We are playing the shouting animation
	//			  2) The animation is in one of the "in action" frames.
	//			  3) We have enough wood "ammunition" (variable wood and shootingCost)
	if (isShouting()
		&& spriteSheet.getCurrentAnim()->getName() == "Shout"
		&& spriteSheet.getCurrentAnim()->isInAction()
		&& wood >= shootingCost
		&& shootCooldown <= 0)
	{
		auto fire = createFire();
		game->addEntity(fire);
		wood -= shootingCost;
		// XI.B (1/2): Set the variable shootCooldown to the cooldown time (defined in shootCooldownTime).
		//        Add another condition to the shooting IF statement that only allows shoowing if shootCooldown <= 0.
		shootCooldown = shootCooldownTime;
		ServiceLocator::getAudio()->playSound("fire");
	}


	// VII.B: If we are attacking but the current animation is no longer playing, set the attacking flag to false.
	//        The same needs to be done for "shouting".
	if (!spriteSheet.getCurrentAnim()->isPlaying())
	{
		if (isAttacking())setAttacking(false);
		if (isShouting())setShouting(false);
		spriteSheet.setAnimation("Idle", true, true);
	}
}


void Player::handleInput(Game& game)
{
		input->update(game);
}

std::shared_ptr<Fire> Player::createFire() const
{
	auto fire = firePool->acquire();

	if (fire)
	{
		Vector2f pos{ getPosition().x + getTextureSize().x * 0.5f, getPosition().y + getTextureSize().y * 0.5f };
		fire->init("img/fire.png", 1.0f); // Set the texture file and scale for the fire entity
		fire->setPosition(pos.x, pos.y);
		Vector2f vel(fireSpeed, 0.f);
		if (spriteSheet.getSpriteDirection() == Direction::Left) vel.x = -vel.x;
		fire->getVelocityComp()->setVelocity(vel.x, vel.y);

		return fire;
	}

	return nullptr;
}


void Player::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}


void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	setPosition(x + cntrFactorX, y + cntrFactorY);
	velocity->setVelocity( 0.0f, 0.0f );
}

