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
        static TextureManager* GetInstance(SDL_Renderer* renderer = nullptr);
        SDL_Texture* LoadTexture(const std::string& file);
        void DrawTexture(const std::string& id, int x, int y, int w, int h);
        void DrawSprite(SDL_Texture* texture, int x, int y);
        void DrawSprite(SDL_Texture* texture, int x, int y, int w, int h);
        void Cleanup();
        ~TextureManager();
};
