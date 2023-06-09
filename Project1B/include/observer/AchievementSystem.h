#pragma once
#include "../entities/Player.h"

class AchievementSystem
{
public:
    static AchievementSystem& getInstance()
    {
        static AchievementSystem instance;
        return instance;
    }

    void notify(const Player& player, const std::string& event);

private:
    AchievementSystem();  // Private constructor

    // Deleted methods to prevent copying
    AchievementSystem(const AchievementSystem&) = delete;
    void operator=(const AchievementSystem&) = delete;

    int totalPotions = 6; 
    int totalShouts = 5; 
};