#include "InputManager.h"

std::unordered_map<SDL_Keycode, bool> InputManager::keyHeld;
std::unordered_map<SDL_Keycode, bool> InputManager::keyDown;
std::unordered_map<SDL_Keycode, bool> InputManager::keyUp;

void InputManager::update(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && !event.key.repeat) {
        keyDown[event.key.keysym.sym] = true;
        keyHeld[event.key.keysym.sym] = true;
    }
    if(event.type == SDL_KEYUP) {
        keyUp[event.key.keysym.sym] = true;
        keyHeld[event.key.keysym.sym] = false;
    }
}

bool InputManager::isKeyDown(SDL_Keycode key) {
    return keyDown[key];
}

bool InputManager::isKeyUp(SDL_Keycode key) {
    return keyUp[key];
}

bool InputManager::isKeyHeld(SDL_Keycode key) {
    return keyHeld[key];
}

void InputManager::resetForNewFrame() {
    keyDown.clear();
    keyUp.clear();
}
