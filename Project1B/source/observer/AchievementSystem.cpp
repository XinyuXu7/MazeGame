#include "../../include/observer/AchievementSystem.h"
#include <iostream>

AchievementSystem::AchievementSystem()
{
    // constructor body
}

void AchievementSystem::notify(const Player& player, const std::string& event)
{
    if (event == "PotionCollected" && player.getPotionCount() == totalPotions)
    {
        std::cout << "Achievement Unlocked: Collected All Potions!" << std::endl;
    }

    if (event == "Shout" && player.getShoutCount() == totalShouts)
    {
        std::cout << "Achievement Unlocked: Shouted 5 Times!" << std::endl;
    }
}