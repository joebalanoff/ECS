#pragma once

#include "ecs/System.h"
#include "ecs/components/Sprite.h"
#include "ecs/components/Position.h"

#include "textures/TextureManager.h"

class RenderSystem : public System {
    public:
        using System::System;

        void update(float deltaTime) override {}

        void render(SDL_Renderer* renderer) override {
            for(Entity entity : entities) {
                auto* position = componentManager->getComponent<Position>(entity);
                auto* sprite = componentManager->getComponent<Sprite>(entity);
                
                if(position && sprite && sprite->texture) {
                    TextureManager::getInstance(renderer)->drawSprite(sprite->texture, position->x, position->y);
                }
            }
        }
};
