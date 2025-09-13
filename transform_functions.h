#ifndef TRANSFORM_FUNCTIONS_H
#define TRANSFORM_FUNCTIONS_H

#pragma once

#include <iostream>
#include <cmath>
#include <functional>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace transform_functions{
    using curveFunction = std::function<float(const int frame, const int frameTotal)>;

    float sigmoidCurve(const uint frame, const uint frameTotal);
    float sineCurve(const uint frame, const uint frameTotal);

    float easeInQuad(const uint frame, const uint frameTotal);
    float easeOutQuad(const uint frame, const uint frameTotal);
    float easeInCubic(const uint frame, const uint frameTotal);
    float easeOutCubic(const uint frame, const uint frameTotal);

    float linearCurve(const uint frame, const uint frameTotal);

    template<typename T>
    T interpol(T start, T end, uint frame, uint frameTotal, const curveFunction& curve);
    
    float transformFloat(const float start, const float end, const uint frame, const uint frameTotal, const curveFunction& curve);
    int transformInt(const int start, const int end, const uint frame, const uint frameTotal, const curveFunction& curve);
    Uint8 transformUint8(const Uint8 start, const Uint8 end, const uint frame, const uint frameTotal, const curveFunction& curve);
    SDL_Color transformColor(const SDL_Color &start, const SDL_Color &end, const uint frame, const uint frameTotal, const curveFunction& curve);

    curveFunction stringToCurveFunction(const std::string& name);
}

#endif