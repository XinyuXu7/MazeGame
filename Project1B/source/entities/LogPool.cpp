#include "../../include/entities/LogPool.h"

LogPool::LogPool(int size) {
    logs.reserve(size);
    inUse.resize(size, true);
    for (int i = 0; i < size; i++) {
        logs.emplace_back(std::make_shared<Log>());
    }
}

std::shared_ptr<Log> LogPool::getLog() {
    for (size_t i = 0; i < logs.size(); i++) {
        if (!inUse[i]) {
            inUse[i] = true;
            return logs[i];
        }
    }
    return nullptr; 
}

void LogPool::returnLog(const std::shared_ptr<Log>& log) {
    for (size_t i = 0; i < logs.size(); i++) {
        if (logs[i] == log) {
            inUse[i] = false;
            break;
        }
    }
}
