#pragma once

#include <iostream>

#include "scenes/Scene.h"
#include "ecs/components/Sprite.h"

#include "prefabs/Player.h"

#include <SDL.h>

class TestingScene : public Scene {
    public:
        TestingScene(SDL_Renderer* renderer) : Scene(renderer) {}

        void onEnter() override {
            Scene::onEnter();

            Player playerPrefab(*this);
            playerPrefab.createInstance();
        }

        void handleEvent(const SDL_Event& event) override {
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                std::cout << "Exit!" << std::endl;
            }
        }

        void update(float deltaTime) override {
            Scene::update(deltaTime);
        }

        void render() override {
            Scene::render(); 
        }
};
