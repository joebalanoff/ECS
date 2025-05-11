#pragma once

#include "ecs/System.h"
#include "ecs/components/Position.h"
#include "ecs/components/Velocity.h"

#include "core/InputManager.h"

class MovementSystem : public System {
    public:
        using System::System;

        void update(float deltaTime) override {
            for(Entity entity : entities) {
                auto* position = componentManager->getComponent<Position>(entity);
                auto* velocity = componentManager->getComponent<Velocity>(entity);

                if(position && velocity) {
                    velocity->vx = InputManager::isKeyHeld(SDLK_d) ? 100 : 0;

                    position->x += velocity->vx * deltaTime;
                    position->y += velocity->vy * deltaTime;
                }
            }
        }

        void render(SDL_Renderer* renderer) override {}
};
