#pragma once

#include "../components/Components.h"

class TTLComponent : public Component // Derive from the Component interface
{
public:
    TTLComponent(int time) : ttl(time) {}
    ~TTLComponent() {}

//    void update() {
//        if (ttl > 0)
//            ttl--;
//   }

    int getTTL() { return ttl; }

    // Implement the getID() function from the Component interface
    ComponentID getID() const override {
        return ComponentID::TTL;
    }

    void decreaseTTL() {
        ttl -= 1;
    }

private:
    int ttl;
};
