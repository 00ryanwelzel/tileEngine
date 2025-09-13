#include "transform_functions.h"

using namespace std;

namespace transform_functions{

    // === Curve Functions ===

    // Ease In & Out

    float sigmoidCurve(const uint frame, const uint frameTotal){
        const float k = 5.0f / (frameTotal / 2.0f);
        const int s = static_cast<int>(frame) - static_cast<int>(frameTotal) / 2;
        return 1.0f / (1.0f + std::exp(-k * s));
    }

    float sineCurve(const uint frame, const uint frameTotal){
        const float t = static_cast<float>(frame) / static_cast<float>(frameTotal);
        return 0.5f * (1.0f - std::cos(static_cast<float>(M_PI) * t));
    }

    // Ease In

    float easeInCubic(uint frame, uint frameTotal) {
        const float t = static_cast<float>(frame) / static_cast<float>(frameTotal);
        return t * t * t;
    }

    float easeInQuad(uint frame, uint frameTotal) {
        const float t = static_cast<float>(frame) / static_cast<float>(frameTotal);
        return t * t;
    }

    // Ease Out

    float easeOutCubic(uint frame, uint frameTotal) {
        const float t = (static_cast<float>(frame) / static_cast<float>(frameTotal));
        return (t - 1.0f) * (t - 1.0f) * (t - 1.0f) + 1;
    }

    float easeOutQuad(uint frame, uint frameTotal) {
        const float t = static_cast<float>(frame) / static_cast<float>(frameTotal);
        return t * (2 - t);
    }

    // Linear

    float linearCurve(const uint frame, const uint frameTotal){
        return static_cast<float>(frame) / static_cast<float>(frameTotal);
    }

    // === Interpol Functions ===

    template<typename T>
    T interpol(T start, T end, uint frame, uint frameTotal, const curveFunction& curve){
        if(start == end) return start;
        if(frame == frameTotal) return end;

        const T height = std::min(start, end);
        const int range = static_cast<int>(end) - static_cast<int>(start);

        const T base = (range < 0) ? (height - range) : height;
        const float normal = curve(frame, frameTotal);

        return static_cast<T>(std::round(base + range * normal));
    }

    // === Interpol Applications ===

    float transformFloat(const float start, const float end, const uint frame, const uint frameTotal, const curveFunction& curve){
        return interpol<float>(start, end, frame, frameTotal, curve);
    }

    int transformInt(const int start, const int end, const uint frame, const uint frameTotal, const curveFunction& curve){
        return interpol<int>(start, end, frame, frameTotal, curve);
    }

    Uint8 transformUint8(const Uint8 start, const Uint8 end, const uint frame, const uint frameTotal, const curveFunction& curve){
        return interpol<Uint8>(start, end, frame, frameTotal, curve);
    }

    SDL_Color transformColor(const SDL_Color &start, const SDL_Color &end, const uint frame, const uint frameTotal, const curveFunction& curve){
        return SDL_Color{
            interpol<Uint8>(start.r, end.r, frame, frameTotal, curve),
            interpol<Uint8>(start.g, end.g, frame, frameTotal, curve),
            interpol<Uint8>(start.b, end.b, frame, frameTotal, curve),
            interpol<Uint8>(start.a, end.a, frame, frameTotal, curve)
        };
    }

    // === JSON Application ===

    curveFunction stringToCurveFunction(const std::string& name) {
        static const std::unordered_map<std::string, curveFunction> lookup = {
            {"sigmoid", sigmoidCurve},
            {"sineCurve", sineCurve},
            {"easeInQuad", easeInQuad},
            {"easeOutQuad", easeOutQuad},
            {"easeInCubic", easeInCubic},
            {"easeOutCubic", easeOutCubic},
            {"linear", linearCurve}
        };

        auto it = lookup.find(name);
        if (it != lookup.end()) {
            return it->second;
        }

        std::cout << "Unknown curveFunction: " << name << " (defaulting to linear)\n";
        return linearCurve;
    }
}
