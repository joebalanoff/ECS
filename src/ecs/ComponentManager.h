#pragma once

#include "Signature.h"
#include <unordered_map>
#include <memory>
#include <cassert>

class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
    public:
        void InsertData(Entity entity, T component) {
            assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");
            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            componentArray[newIndex] = component;
            size++;
        }

        void RemoveData(Entity entity) {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");
            size_t indexOfRemovedEntity = entityToIndexMap[entity];
            size_t indexOfLastElement = size - 1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

            Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);
            size--;
        }

        T& GetData(Entity entity) {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
            return componentArray[entityToIndexMap[entity]];
        }

        void EntityDestroyed(Entity entity) override {
            if(entityToIndexMap.find(entity) != entityToIndexMap.end())
                RemoveData(entity);
        }
    
    private:
        std::array<T, 1000> componentArray{};
        std::unordered_map<Entity, size_t> entityToIndexMap;
        std::unordered_map<size_t, Entity> indexToEntityMap;
        size_t size = 0;
};

class ComponentManager {
    public:
        template<typename T>
        void RegisterComponent() {
            const char* typeName = typeid(T).name();
            componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
        }

        template<typename T>
        void AddComponent(Entity entity, T component) {
            GetComponentArray<T>()->InsertData(entity, component);
        }

        template<typename T>
        void RemoveComponent(Entity entity) {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template<typename T>
        T& GetComponent(Entity entity) {
            return GetComponentArray<T>()->GetData(entity);    
        }

        void EntityDestroyed(Entity entity) {
            for(auto const& pair : componentArrays) {
                auto const& componentArray = pair.second;
                componentArray->EntityDestroyed(entity);
            }
        }

    private:
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray() {
            const char* typeName = typeid(T).name();
            return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
        }
};
