#include "../../include/entities/PotionPool.h"

PotionPool::PotionPool(int size) {
    potions.reserve(size);
    inUse.resize(size, true);
    for (int i = 0; i < size; i++) {
        potions.emplace_back(std::make_shared<Potion>());
    }
}

std::shared_ptr<Potion> PotionPool::getPotion() {
    for (size_t i = 0; i < potions.size(); i++) {
        if (!inUse[i]) {
            inUse[i] = true;
            return potions[i];
        }
    }
    return nullptr;  
}

void PotionPool::returnPotion(const std::shared_ptr<Potion>& potion) {
    for (size_t i = 0; i < potions.size(); i++) {
        if (potions[i] == potion) {
            inUse[i] = false;
            break;
        }
    }
}
