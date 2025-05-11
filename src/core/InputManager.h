#pragma once

#include <SDL.h>
#include <unordered_map>

class InputManager {
    public:
        static void update(SDL_Event& event);

        static bool isKeyDown(SDL_Keycode key);
        static bool isKeyUp(SDL_Keycode key);
        static bool isKeyHeld(SDL_Keycode key);

        static void resetForNewFrame();

    private:
        static std::unordered_map<SDL_Keycode, bool> keyHeld;
        static std::unordered_map<SDL_Keycode, bool> keyDown;
        static std::unordered_map<SDL_Keycode, bool> keyUp;
};
