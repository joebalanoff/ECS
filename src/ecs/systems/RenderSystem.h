#pragma once

#include "ecs/ECS.h"

#include "ecs/components/Sprite.h"
#include "ecs/components/Position.h"

#include "textures/TextureManager.h"

class RenderSystem : public System {
    public:
        RenderSystem(ComponentManager& compMgr) : componentManager(compMgr) {} 

        void render(SDL_Renderer* renderer) override {
            for(auto entity : entities) {
                auto& sprite = componentManager.GetComponent<Sprite>(entity);
                auto& position = componentManager.GetComponent<Position>(entity);

                TextureManager::GetInstance()->DrawSprite(sprite.texture, position.x, position.y);
            }
        }
    private:
        ComponentManager& componentManager;
};
