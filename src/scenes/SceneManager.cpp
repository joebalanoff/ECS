#include "SceneManager.h"

void SceneManager::pushScene(std::unique_ptr<Scene> scene) {
    if(!scenes.empty()) scenes.top()->onExit();
    scenes.push(std::move(scene));
    scenes.top()->onEnter();
}

void SceneManager::popScene() {
    if(!scenes.empty()) {
        scenes.top()->onExit();
        scenes.pop();
    } 
    if(!scenes.empty()) scenes.top()->onEnter();
}

void SceneManager::changeScene(std::unique_ptr<Scene> scene) {
    popScene();
    pushScene(std::move(scene));
}

void SceneManager::handleEvent(const SDL_Event& event) {
    if(!scenes.empty()) scenes.top()->handleEvent(event);
}

void SceneManager::update(float deltaTime) {
    if(!scenes.empty()) scenes.top()->update(deltaTime);
}

void SceneManager::render() {
    if(!scenes.empty()) scenes.top()->render();
}
