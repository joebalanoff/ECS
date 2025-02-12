#pragma once

#include "scenes/Scene.h"

class Prefab {
    public:
        Prefab(Scene& scene) : scene(scene) {}

        virtual Entity createInstance() = 0;
    protected:
        Scene& scene;

        Entity createEntity() {
            return scene.createEntity();    
        }

        template<typename T>
        void registerSystem(std::unordered_set<std::type_index> requiredComponents) {
            scene.registerSystem<T>(requiredComponents);
        }

        template<typename T>
        void registerComponent() {
            scene.registerComponent<T>();
        }

        template<typename T>
        void addComponent(Entity entity, T component) {
            scene.addComponent(entity, component);
        }
};
