#pragma once
#include "Entity.h"
#include "../Components/HealthComponent.h"
#include "../utils/Vector2.h"
#include "../components/VelocityComponent.h"
#include "../components/InputComponent.h" 
#include "../entities/FirePool.h"

class Fire;
class InputComponent;

class Player : public Entity
{
public:

    const float playerSpeed = 100.f;
    const int startingHealth = 60;
    const int maxHealth = 100;
    const int maxWood = 100;
    const int shootingCost = 20;
    const float fireSpeed = 200.f;
    const float shootCooldownTime = 3.f; //in seconds

    Player();
    ~Player();

    virtual void update(Game* game, float elapsed = 1.0f) override;

    void handleInput(Game& game);

    bool isAttacking() const { return attacking; }
    void setAttacking(bool at) { attacking = at; }

    bool isShouting() const { return shouting; }
    void setShouting(bool sh) { shouting = sh; }

    std::shared_ptr<HealthComponent> getHealthComp() { return health; }

    int getWood() const { return wood; }
    void addWood(int w);

    bool hasSpriteSheet() const { return isSpriteSheet; }

    void positionSprite(int row, int col, int spriteWH, float tileScale);

    std::shared_ptr<VelocityComponent> getVelocityComp() { return velocity; }


    int getShoutCount() const { return shoutCount; } // getter for shout count
    void incrementShoutCount() { shoutCount++; }    // increment shout count

    void incrementPotionCount() { ++potionCount; }
    int getPotionCount() const {return potionCount;}


private:

    std::shared_ptr<Fire> createFire() const;

    bool attacking;
    bool shouting;
    std::shared_ptr<HealthComponent> health;
    int wood;
    float shootCooldown;

    // Change the unique pointer to an InputComponent
    std::shared_ptr<InputComponent> input;

    // Add the shared pointer to VelocityComponent:
    std::shared_ptr<VelocityComponent> velocity;

    int shoutCount;
    int potionCount;

    std::shared_ptr<FirePool> firePool;
};
