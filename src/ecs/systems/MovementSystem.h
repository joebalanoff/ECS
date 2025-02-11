#pragma once

#include "ecs/System.h"
#include "ecs/components/Position.h"
#include "ecs/components/Velocity.h"

class MovementSystem : public System {
    public:
        using System::System;

        void update(float deltaTime) override {
            for(Entity entity : entities) {
                auto* position = componentManager->getComponent<Position>(entity);
                auto* velocity = componentManager->getComponent<Velocity>(entity);

                if(position && velocity) {
                    position->x += velocity->vx * deltaTime;
                    position->y += velocity->vy * deltaTime;
                }
            }
        }

        void render(SDL_Renderer* renderer) override {}
};
