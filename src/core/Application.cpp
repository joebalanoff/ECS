#include "Application.h"
#include "textures/TextureManager.h"

#include "../scenes/game/TestingScene.h"

#include <iostream>

Application::Application() : window(nullptr), renderer(nullptr), isRunning(false) { }

Application::~Application() {
    shutdown();
}

bool Application::initialize(const char* title, int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << '\n';
        return false;
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if(!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) return false;

    TextureManager::GetInstance(renderer);

    sceneManager.pushScene(std::make_unique<TestingScene>(renderer));

    isRunning = true;
    return true;
}

void Application::run() {
    const int FPS = 60;
    const float frameDelay = 1000.0f / FPS;
    Uint32 frameStart = SDL_GetTicks();
    float deltaTime = 1.0 / FPS;

    while(isRunning) {
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - frameStart) / 1000.0f;

        frameStart = currentTime;

        processInput();
        update(deltaTime);
        render();

        int frameTime = SDL_GetTicks() - currentTime;
        if (frameDelay > frameTime) {
            SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));
        }    
    }
}

void Application::processInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            isRunning = false;
        }
        sceneManager.handleEvent(event);
    }
}

void Application::update(float deltaTime) {
    sceneManager.update(deltaTime);
}

void Application::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    sceneManager.render();

    SDL_RenderPresent(renderer);
}

void Application::shutdown() {
    if(renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if(window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    TextureManager::GetInstance()->Cleanup();
    IMG_Quit();
    SDL_Quit();
}
