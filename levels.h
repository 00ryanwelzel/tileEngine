#ifndef LEVELS_H
#define LEVELS_H

#pragma once

#include "sprites.h"

#include "transform_chains.h"
#include "transform_functions.h"
#include "transform_loader.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <nlohmann/json.hpp>

class levels{
    private:

    struct tile{
        bool isXtransform;
        uint x;
        size_t xIndex;

        bool isYtransform;
        uint y;
        size_t yIndex;

        bool isWtransform;
        uint w;
        size_t wIndex;

        bool isHtransform;
        uint h;
        size_t hIndex;

        size_t spriteIndex;

        bool isPrimaryTransform;
        size_t primaryIndex;

        bool isSecondaryTransform;
        size_t secondaryIndex;

        uint behavior;
    };

    std::vector<std::vector<tile>> level;

    std::vector<std::string> spriteNames;
    std::vector<sprites::spriteDef> sprites;

    std::vector<std::string> colorTransformNames;
    std::vector<transform_chains::colorTransformDef> colorTransforms;

    std::vector<std::string> intTransformNames;
    std::vector<transform_chains::intTransformDef> intTransforms;

    std::vector<std::string> colorNames;
    std::vector<SDL_Color> colors;


    public:

    void loadLevel(const std::string& levelName);

    void drawLevel(
        SDL_Renderer* renderer,
        const uint frame,
        const int globalX, const int globalY, 
        const int globalW, const int globalH
    );

    void loadTiles(const std::string& path);
    
    void loadSprites(const std::string& path);
    void loadColorTransforms(const std::string& path);
    void loadIntTransforms(const std::string& path);
    void loadColors(const std::string& path);

};

#endif