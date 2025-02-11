#pragma once

#include "Signature.h"
#include <unordered_set>

class EntityManager {
    private:
        uint32_t nextEntity = 0;
        std::unordered_set<Entity> activeEntities;

    public:
        Entity createEntity() {
            Entity entity = nextEntity++;
            activeEntities.insert(entity);
            return entity;
        }

        void destroyEntity(Entity entity) {
            activeEntities.erase(entity);
        }
};
