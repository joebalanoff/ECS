#pragma once

#include <memory>
#include <stack>

#include "Scene.h"
#include <SDL.h>

class SceneManager {
    private:
        std::stack<std::unique_ptr<Scene>> scenes;
    public:
        void pushScene(std::unique_ptr<Scene> scene);
        void popScene();
        void changeScene(std::unique_ptr<Scene> scene);

        void handleEvent(const SDL_Event& event);
        
        void update(float deltaTime);
        void render();
};
