#include "../../include/entities/FirePool.h"

FirePool::FirePool(int poolSize)
{
    for (int i = 0; i < poolSize; i++)
    {
        auto fire = std::make_shared<Fire>();
        pool.push_back(fire);
    }
}

FirePool::~FirePool()
{}

std::shared_ptr<Fire> FirePool::acquire()
{
    for (auto& fire : pool)
    {
        if (!fire->isInUse())
        {
            fire->setInUse(true);
            return fire;
        }
    }

    return nullptr;
}

void FirePool::release(std::shared_ptr<Fire> fire)
{
    fire->setInUse(false);
}
