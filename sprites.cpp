#include "sprites.h"

using namespace std;

namespace sprites{

    // === Load Function ===

    void loadSprite(
        const std::string& spriteName, 
        const nlohmann::json& sprites, 
        std::vector<spriteLayer>& outSprite
    ){
        outSprite.clear();

        if (!sprites.contains(spriteName)) {
            std::cerr << "Sprite not found: " << spriteName << std::endl;
            return;
        }

        const auto& spriteDef = sprites.at(spriteName);

        // Skip undefined sprites
        if (!spriteDef.contains("layers")) {
            return;
        }

        for (const auto& layer : spriteDef["layers"]) {
            spriteLayer l;
            l.colorKey = layer.value("color", "base");

            const auto& rect = layer.at("rect");
            l.x = rect.value("x", 0.0f);
            l.y = rect.value("y", 0.0f);
            l.w = rect.value("w", 1.0f);
            l.h = rect.value("h", 1.0f);

            outSprite.push_back(l);
        }
    }

    // === Draw Function ===

    void drawSprite(
        SDL_Renderer* renderer,
        std::vector<spriteLayer>& sprite,
        const SDL_Color& primary,
        const SDL_Color& secondary,
        const SDL_Color& base,
        const int x, const int y, 
        const int w, const int h
    ){
        for (spriteLayer &layer : sprite) {
            SDL_Color color;

            if (layer.colorKey == "primary") color = primary;
            else if (layer.colorKey == "secondary") color = secondary;
            else if (layer.colorKey == "base") color = base;
            else continue;

            const float nx = layer.x;
            const float ny = layer.y;
            const float nw = layer.w;
            const float nh = layer.h;

            SDL_Rect rect = {
                x + static_cast<int>(nx * w),
                y + static_cast<int>(ny * h),
                static_cast<int>(nw * w),
                static_cast<int>(nh * h)
            };

            drawRect(renderer, rect, color);
        }
    }   
    
    // === Helper Functions ===

    void drawRect(SDL_Renderer* renderer, const SDL_Rect& rect, const SDL_Color& color){
        setRenderColor(renderer, color);
        SDL_RenderFillRect(renderer, &rect);
    }

    void setRenderColor(SDL_Renderer* renderer, const SDL_Color& color){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
}