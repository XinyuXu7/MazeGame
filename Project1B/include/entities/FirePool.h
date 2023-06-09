#pragma once
#include "Fire.h"
#include <vector>
#include <memory>

class FirePool
{
public:
    FirePool(int poolSize);
    ~FirePool();

    std::shared_ptr<Fire> acquire();
    void release(std::shared_ptr<Fire> fire);

private:
    std::vector<std::shared_ptr<Fire>> pool;
};
