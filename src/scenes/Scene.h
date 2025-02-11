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
        std::unique_ptr<SystemManager> systemManager;

    public:
        Scene(SDL_Renderer* renderer) : renderer(renderer) {
            entityManager = std::make_unique<EntityManager>();
            componentManager = std::make_unique<ComponentManager>();
            systemManager = std::make_unique<SystemManager>(componentManager.get());
        }

        virtual ~Scene() = default;
        
        virtual void handleEvent(const SDL_Event& event) = 0;

        virtual void onEnter() {
            componentManager->registerComponent<Position>();
            componentManager->registerComponent<Velocity>();
            componentManager->registerComponent<Sprite>();

            systemManager->registerSystem<MovementSystem>({typeid(Position), typeid(Velocity)});
            systemManager->registerSystem<RenderSystem>({typeid(Position), typeid(Sprite)});
        }

        virtual void onExit() {}

        virtual void update(float deltaTime) {
            systemManager->update(deltaTime);
        }

        virtual void render(){
            systemManager->render(renderer);    
        }

        Entity createEntity() {
            return entityManager->createEntity();
        }

        template<typename T>
        void registerComponent() {
            componentManager->registerComponent<T>();
        }

        template<typename T>
        void addComponent(Entity entity, T component) {
            componentManager->addComponent(entity, component);
            systemManager->checkSystemRequirements<T>(entity);        
        }
};
