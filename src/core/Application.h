#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "../scenes/SceneManager.h"

class Application {
    public:
        Application();
        ~Application();

        bool initialize(const char* title, int width, int height);
        void run();
        void shutdown();
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool isRunning;
        
        void processInput();
        void update(float deltaTime);
        void render();

        SceneManager sceneManager;
};
