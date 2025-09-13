#ifndef TRANSFORM_CHAINS_H
#define TRANSFORM_CHAINS_H

#pragma once

#include "transform_functions.h"

#include <iostream>
#include <cmath>
#include <functional>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <nlohmann/json.hpp>

namespace transform_chains{

    template<typename T>
    struct transform_base{
        T from, to;
        transform_functions::curveFunction _curveFunction;
        uint frameTotal;
        bool no_op;
    };

    using color_transform = transform_base<SDL_Color>;
    using int_transform = transform_base<int>;
    using Uint8_transform = transform_base<Uint8>;
    using float_transform = transform_base<float>;

    template<typename T>
    struct transformDef{
        std::vector<transform_base<T>> transform;
    };

    using colorTransformDef = transformDef<SDL_Color>;
    using intTransformDef = transformDef<int>;
    using Uint8TransformDef = transformDef<Uint8>;
    using floatTransformDef = transformDef<float>;
 
    template<typename T>
    uint getFrames(const std::vector<T>& transformContainers);

    template<typename Tin, typename Tout>
    Tout getCurrent(const std::vector<Tin>& transformContainers, const uint frame);
    
    uint getColorChainFrames(const std::vector<color_transform>& transformContainers);
    uint getIntChainFrames(const std::vector<int_transform>& transformContainers);
    uint getUint8ChainFrames(const std::vector<Uint8_transform>& transformContainers);
    uint getFloatChainFrames(const std::vector<float_transform>& transformContainers);

    int getCurrentInt(const std::vector<int_transform>& transformContainers, const uint frame);
    Uint8 getCurrentUint8(const std::vector<Uint8_transform>& transformContainers, const uint frame);
    SDL_Color getCurrentColor(const std::vector<color_transform>& transformContainers, const uint frame);
    float getCurrentFloat(const std::vector<float_transform>& transformContainers, const uint frame);

}

#endif