#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>

class TextureManager {
    private:
        std::unordered_map<std::string, SDL_Texture*> textureMap;
        SDL_Renderer* renderer;
        static TextureManager* instance;

        TextureManager(SDL_Renderer* renderer);
    public:
        static TextureManager* getInstance(SDL_Renderer* renderer = nullptr);
        SDL_Texture* loadTexture(const std::string& file);
        void drawTexture(const std::string& id, int x, int y, int w, int h);
        void drawSprite(SDL_Texture* texture, int x, int y);
        void drawSprite(SDL_Texture* texture, int x, int y, int w, int h);
        void cleanup();
        ~TextureManager();
};
