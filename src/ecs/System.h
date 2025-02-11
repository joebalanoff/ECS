#pragma once

#include <SDL.h>

#include <set>
#include <unordered_set>

#include <typeindex>
#include "ComponentManager.h"

class System {
    protected:
        std::set<Entity> entities;
        std::unordered_set<std::type_index> requiredComponents;

        ComponentManager* componentManager;

    public:
        explicit System(ComponentManager* componentManager, std::unordered_set<std::type_index> requiredComponents) : componentManager(componentManager), requiredComponents(requiredComponents) {}
        virtual ~System() = default;

        virtual void update(float deltaTime) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;

        void addEntity(Entity entity) {
            entities.insert(entity);
        }

        void removeEntity(Entity entity) {
            entities.erase(entity);
        }

        const std::unordered_set<std::type_index>& getRequiredComponents() const {
            return requiredComponents;
        }
};
