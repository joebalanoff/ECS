#include "EntityManager.h"

EntityManager::EntityManager() {
    for(Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        availableEntities.push(entity);
    }
}

Entity EntityManager::CreateEntity() {
    if(livingEntityCount >= MAX_ENTITIES) {
        throw std::runtime_error("Too many entities!");
    }
    Entity id = availableEntities.front();
    availableEntities.pop();
    ++livingEntityCount;
    return id;
}

void EntityManager::DestroyEntity(Entity entity) {
    availableEntities.push(entity);
    entitySignatures[entity].reset();
    --livingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
    entitySignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
    return entitySignatures[entity];
}
