#pragma once

#include "textures/TextureManager.h"

struct Sprite {
    SDL_Texture* texture;

    Sprite(SDL_Texture* texture = nullptr) : texture(texture) {}
};
