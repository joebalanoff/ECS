#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include "System.h"

class SystemManager {
    private:
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
        ComponentManager* componentManager;

    public:
        SystemManager(ComponentManager* componentManager) : componentManager(componentManager) {}

        template<typename T>
        std::shared_ptr<T> registerSystem(std::unordered_set<std::type_index> requiredComponents) {            
            auto system = std::make_shared<T>(componentManager, requiredComponents);            
            systems[typeid(T)] = system;
            return system;
        }

        template<typename T>
        T* getSystem() {
            auto it = systems.find(typeid(T));
            if(it != systems.end()) {
                return static_cast<T*>(it->second.get());
            }
            return nullptr;
        }

        template<typename T>
        void checkSystemRequirements(Entity entity) {
            for(auto& [systemType, system] : systems) {
                bool meetsRequirements = true;

                for(const auto& requiredComponent : system->getRequiredComponents()) {
                    if(!componentManager->hasComponent(entity, requiredComponent)) {
                        meetsRequirements = false;
                        break;
                    }
                }

                if(meetsRequirements) {
                    system->addEntity(entity);
                }
            }
        }

        void update(float deltaTime) {
            for(auto& system : systems) {
                system.second->update(deltaTime);
            }
        }

        void render(SDL_Renderer* renderer) {
            for(auto& system : systems) {
                system.second->render(renderer);
            }
        }
};
