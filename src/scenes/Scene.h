#pragma once

#include <SDL.h>
#include <vector>
#include <memory>

#include "ecs/ECS.h"

#include "ecs/systems/RenderSystem.h"
#include "ecs/systems/MovementSystem.h"

class Scene {
    protected:
        SDL_Renderer* renderer;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;
        std::vector<std::unique_ptr<System>> systems;

    public:
        Scene(SDL_Renderer* renderer) : renderer(renderer) {
            entityManager = std::make_unique<EntityManager>();
            componentManager = std::make_unique<ComponentManager>();
        }

        virtual ~Scene() = default;
        
        virtual void handleEvent(const SDL_Event& event) = 0;

        virtual void onEnter() {
            componentManager->RegisterComponent<Position>();
            componentManager->RegisterComponent<Velocity>();
            componentManager->RegisterComponent<Sprite>();

            addSystem<MovementSystem>();
            addSystem<RenderSystem>();
        }

        virtual void onExit() {}

        virtual void update(float deltaTime) {
            for(auto& system : systems) {
                system->update(deltaTime);
            }
        }

        virtual void render(){
            for(auto& system : systems) {
                system->render(renderer);
            }
        }

        template<typename T, typename... Args>
        void addSystem(Args&&... args) {
            systems.push_back(std::make_unique<T>(*componentManager, std::forward<Args>(args)...));
        }

        template<typename T>
        void assignEntityToSystem(Entity entity) {
            for(auto& system : systems) {
                for(auto& system : systems) {
                    if(auto castedSystem = dynamic_cast<T*>(system.get())) {
                        castedSystem->entities.insert(entity);
                        return;
                    }
                }
            }
        }

        template<typename T>
        T* getSystem() {
            for(auto& system : systems) {
                if(auto castedSystem = dynamic_cast<T*>(system.get())) {
                    return castedSystem;
                }
            }
            return nullptr;
        }
        
        Entity createEntity() {
            return entityManager->CreateEntity();
        }

        template<typename T>
        void registerComponent() {
            componentManager->RegisterComponent<T>();
        }

        template<typename T>
        void addComponent(Entity entity, T component) {
            componentManager->AddComponent(entity, component);
        }
};
