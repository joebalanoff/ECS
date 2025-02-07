#pragma once

#include "Signature.h"
#include <vector>
#include <queue>

class EntityManager {
    public:
        EntityManager();

        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        void SetSignature(Entity entity, Signature signature);
        Signature GetSignature(Entity entity);
    private:
        std::queue<Entity> availableEntities;
        std::vector<Signature> entitySignatures;
        std::size_t livingEntityCount = 0;
};
