#pragma once

#include <vector>
#include <memory>
#include "StaticEntities.h"

class PotionPool {
private:
    std::vector<std::shared_ptr<Potion>> potions;
    std::vector<bool> inUse;

public:
    PotionPool(int size);

    std::shared_ptr<Potion> getPotion();
    void returnPotion(const std::shared_ptr<Potion>& potion);
};
