#pragma once

#include "ecs/System.h"
#include "ecs/components/Velocity.h"

class PlayerController : public System {
    public:
        using System::System;

        void update(float deltaTime) override {
            
        }

        void render(SDL_Renderer* renderer) override {}
};
