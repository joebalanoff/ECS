#pragma once

#include <typeindex>
#include <unordered_map>
#include <memory>
#include <vector>

#include "Signature.h"

class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
};

template<typename T>
class ComponentArray : public IComponentArray {
    private: 
        std::unordered_map<Entity, T> componentData;
        
    public:
        void insert(Entity entity, T component) {
            componentData[entity] = component;
        }

        void remove(Entity entity) {
            componentData.erase(entity);
        }

        T* getComponent(Entity entity) {
            if(componentData.find(entity) != componentData.end()) {
                return &componentData[entity];
            }
            return nullptr;
        }
};

class ComponentManager {
    private:
        std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> componentArrays;

    public:
        template<typename T>
        void registerComponent() {
            componentArrays[typeid(T)] = std::make_unique<ComponentArray<T>>();
        }

        template<typename T>
        void addComponent(Entity entity, T component) {
            getComponentArray<T>()->insert(entity, component);
        }

        template<typename T>
        void removeComponent(Entity entity) {
            getComponentArray<T>()->remove(entity);
        }

        template<typename T>
        T* getComponent(Entity entity) {
            return getComponentArray<T>()->getComponent(entity);
        }

        bool hasComponent(Entity entity, std::type_index componentType) {
            auto it = componentArrays.find(componentType);
            if(it == componentArrays.end()) return false;

            IComponentArray* baseArray = it->second.get();
            auto* componentArray = static_cast<ComponentArray<std::remove_pointer_t<decltype(baseArray)>>*>(baseArray);

            return componentArray->getComponent(entity) != nullptr;
        }

    private:
        template<typename T>
        ComponentArray<T>* getComponentArray() {
            return static_cast<ComponentArray<T>*>(componentArrays[typeid(T)].get());
        }
};
