#include "TextureManager.h"
#include <iostream>

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager(SDL_Renderer* renderer) : renderer(renderer) {}

TextureManager* TextureManager::getInstance(SDL_Renderer* renderer) {
    if(!instance) {
        if(!renderer) {
            return nullptr;
             }
        instance = new TextureManager(renderer);
    }
    return instance;
}

SDL_Texture* TextureManager::loadTexture(const std::string& file) {
    std::string filePath = "../assets/" + file; 
    if(textureMap.find(filePath) != textureMap.end()) {
        return textureMap[filePath];
    }
    
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if(!surface) {
        std::cerr << "Failed to load image: " << filePath << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if(!texture) {
        std::cerr << "Failed to create texture: " << filePath << std::endl;
        return nullptr;
    }

    textureMap[filePath] = texture;
    return texture;
}

void TextureManager::drawTexture(const std::string& id, int x, int y, int w, int h) {
    std::string lookUp = "../assets/" + id;
    if(textureMap.find(lookUp) == textureMap.end()) return;

    SDL_Rect destRect = { x, y, w, h};
    SDL_RenderCopy(renderer, textureMap[lookUp], nullptr, &destRect);
}

void TextureManager::drawSprite(SDL_Texture* texture, int x, int y) {
    if(!texture) {
        std::cerr << "DrawSprite: Texture is null!" << std::endl;
        return;
    }
    
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    this->drawSprite(texture, x, y, width, height);
}

void TextureManager::drawSprite(SDL_Texture* texture, int x, int y, int w, int h) {
    if(!texture) {
        std::cerr << "DrawSprite: Texture is null!" << std::endl;
        return;
    }

    SDL_Rect destRect = { x, y, w, h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void TextureManager::cleanup(){
    for(auto& pair : textureMap) {
        SDL_DestroyTexture(pair.second);
    }
    textureMap.clear();
}

TextureManager::~TextureManager() {
    cleanup();
    instance = nullptr;
}
