#ifndef TRANSFORM_LOADER_H
#define TRANSFORM_LOADER_H

#pragma once

#include "transform_chains.h"
#include "transform_functions.h"

#include <iostream>
#include <cmath>
#include <functional>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <nlohmann/json.hpp>

namespace transform_loader{

    void loadColorChain(
        const std::string& chainName, 
        const nlohmann::json& chains, 
        std::vector<transform_chains::color_transform>& outChain
    );

    void loadIntChain(
        const std::string& chainName, 
        const nlohmann::json& chains, 
        std::vector<transform_chains::int_transform>& outChain
    );

    void loadUint8Chain(
        const std::string& chainName, 
        const nlohmann::json& chains, 
        std::vector<transform_chains::Uint8_transform>& outChain
    );

    void loadFloatChain(
        const std::string& chainName, 
        const nlohmann::json& chains, 
        std::vector<transform_chains::float_transform>& outChain
    );

}

#endif