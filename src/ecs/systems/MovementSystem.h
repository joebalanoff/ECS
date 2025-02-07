#pragma once

#include "ecs/ECS.h"
#include "ecs/components/Position.h"
#include "ecs/components/Velocity.h"

#include <iostream>

class MovementSystem : public System {
    public:
        MovementSystem(ComponentManager& compMgr) : componentManager(compMgr) {}

        void update(float deltaTime) override {
            for(auto entity : entities) {
                Position& pos = componentManager.GetComponent<Position>(entity);
                Velocity& vel = componentManager.GetComponent<Velocity>(entity);
                pos.x += vel.vx * deltaTime;
                pos.y += vel.vy * deltaTime;
            }
        }

    private:
        ComponentManager& componentManager;
};
