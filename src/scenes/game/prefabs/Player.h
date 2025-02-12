#pragma once

#include "ecs/ECS.h"
#include "scenes/Prefab.h"

class Player : public Prefab {
    public:
        Player(Scene& scene) : Prefab(scene) {}
        
        Entity createInstance() {
            Entity player = createEntity();
            
            addComponent(player, Position { 100.0f, 100.0f });
            addComponent(player, Velocity { 100, 100 });
            addComponent(player, Sprite { TextureManager::getInstance()->loadTexture("circle-128.png") });

            return player;
        }
};
