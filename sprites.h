#ifndef SPRITES_H
#define SPRITES_H

#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <nlohmann/json.hpp>

namespace sprites{

    struct spriteLayer{
        std::string colorKey;
        float x, y, w, h;
    };

    struct spriteDef{
        std::vector<spriteLayer> layers;
    };

    void loadSprite(
        const std::string& spriteName, 
        const nlohmann::json& sprites, 
        std::vector<spriteLayer>& outSprite
    );

    void drawSprite(
        SDL_Renderer* renderer, 
        std::vector<spriteLayer>& sprite,
        const SDL_Color& primary, 
        const SDL_Color& secondary, 
        const SDL_Color& base, 
        const int x, const int y, 
        const int w, const int h
    );

    void drawRect(SDL_Renderer* renderer, const SDL_Rect& rect, const SDL_Color& color);
    void setRenderColor(SDL_Renderer* renderer, const SDL_Color& color);
}

#endif