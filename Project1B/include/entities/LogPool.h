#pragma once

#include <vector>
#include <memory>
#include "StaticEntities.h"

class LogPool {
private:
    std::vector<std::shared_ptr<Log>> logs;
    std::vector<bool> inUse;

public:
    LogPool(int size);

    std::shared_ptr<Log> getLog();
    void returnLog(const std::shared_ptr<Log>& log);
};
