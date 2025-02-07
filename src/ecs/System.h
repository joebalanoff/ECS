#pragma once

#include <SDL.h>

#include <set>
#include "ComponentManager.h"

class System {
    public:
        std::set<Entity> entities;

        virtual ~System() = default;
        virtual void update(float deltaTime) {}
        virtual void render(SDL_Renderer* renderer) {}
};
