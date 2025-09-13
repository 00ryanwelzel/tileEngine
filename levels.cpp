#include "levels.h"

using namespace std;
using namespace transform_chains;
using namespace transform_functions;

void levels::loadLevel(const std::string& levelName){
    // Instantiate all reused level values
    loadColors(levelName);
    loadSprites(levelName);
    loadColorTransforms(levelName);
    loadIntTransforms(levelName);

    // Instantiate the level itself
    loadTiles(levelName);
}

// ====================================
// === Draw Level Using Tile Values ===
// ====================================

void levels::drawLevel(
    SDL_Renderer* renderer,
    const uint frame,
    const int globalX, const int globalY, 
    const int globalW, const int globalH
){
    for (size_t y = 0; y < level.size(); ++y){
        for (size_t x = 0; x < level[y].size(); ++x){
            const tile& t = level[y][x];

            // Get the sprite at tile.spriteIndex
            if (t.spriteIndex >= sprites.size()) continue;
            std::vector<sprites::spriteLayer> sprite = sprites[t.spriteIndex].layers;

            SDL_Color primary{255,255,255,255};
            if (t.isPrimaryTransform) {
                primary = transform_chains::getCurrentColor(colorTransforms[t.primaryIndex].transform, frame);
            } else {
                primary = colors[t.primaryIndex];
            }

            SDL_Color secondary{255,255,255,255};
            if (t.isSecondaryTransform) {
                secondary = transform_chains::getCurrentColor(colorTransforms[t.secondaryIndex].transform, frame);
            } else {
                secondary = colors[t.secondaryIndex];
            }

            SDL_Color base{0,0,0,255};

            int screenX = globalX + static_cast<int>(x * globalW);
            if(t.isXtransform){
                screenX = transform_chains::getCurrentInt(intTransforms[t.xIndex].transform, frame);
            }

            int screenY = globalY + static_cast<int>(y * globalH);
            if(t.isYtransform){
                screenX = transform_chains::getCurrentInt(intTransforms[t.yIndex].transform, frame);
            }

            sprites::drawSprite(
                renderer, sprite, 
                primary, secondary, base, 
                screenX, screenY, globalW, globalH
            );
        }
    }
}

// ==========================================
// === Load Information Into Tile Objests ===
// ==========================================

void levels::loadTiles(const std::string& path){
    level.clear();

    nlohmann::json tilesData;

    std::ifstream f(path + "/level.json");
    if(!f.is_open()) return;
    f >> tilesData;

    const auto& spriteArray = tilesData.at("levelSprites");
    const auto& primaryArray = tilesData.at("levelPrimaries");
    const auto& secondaryArray = tilesData.at("levelSecondaries");
    const auto& xArray = tilesData.at("levelXbehaviors");
    const auto& yArray = tilesData.at("levelYbehaviors");

    size_t rows = spriteArray.size();
    size_t cols = spriteArray[0].size();

    level.resize(rows, std::vector<tile>(cols));

    for (size_t y = 0; y < rows; ++y) {
        for (size_t x = 0; x < cols; ++x) {
            tile t{};

            // === Sprites ===
            std::string spriteName = spriteArray[y][x];
            auto spriteIt = std::find(spriteNames.begin(), spriteNames.end(), spriteName);

            if (spriteIt != spriteNames.end()){
                t.spriteIndex = std::distance(spriteNames.begin(), spriteIt);
            } else {
                t.spriteIndex = 0;
            }

            // === Primary Colors ===
            std::string primaryName = primaryArray[y][x];
            auto primIt = std::find(colorNames.begin(), colorNames.end(), primaryName);
            auto primTfIt = std::find(colorTransformNames.begin(), colorTransformNames.end(), primaryName);

            if (primIt != colorNames.end()){
                t.isPrimaryTransform = false;
                t.primaryIndex = std::distance(colorNames.begin(), primIt);
            } else {
                t.isPrimaryTransform = true;
                t.primaryIndex = std::distance(colorTransformNames.begin(), primTfIt);
            }

            // === Secondary Colors ===
            std::string secondaryName = secondaryArray[y][x];
            auto secIt = std::find(colorNames.begin(), colorNames.end(), secondaryName);
            auto secTfIt = std::find(colorTransformNames.begin(), colorTransformNames.end(), secondaryName);

            if (secIt != colorNames.end()){
                t.isSecondaryTransform = false;
                t.secondaryIndex = std::distance(colorNames.begin(), secIt);
            } else {
                t.isSecondaryTransform = true;
                t.secondaryIndex = std::distance(colorTransformNames.begin(), secTfIt);
            }

            // === X ===
            std::string xName = xArray[y][x];
            auto xIt = std::find(intTransformNames.begin(), intTransformNames.end(), xName);

            t.x = x;

            if(xIt != intTransformNames.end()){
                t.isXtransform = true;
                t.xIndex = std::distance(intTransformNames.begin(), xIt);
            } else {
                t.isXtransform = false;
                t.xIndex = 0;
            }

            // === Y ===
            std::string yName = yArray[y][x];
            auto yIt = std::find(intTransformNames.begin(), intTransformNames.end(), yName);

            t.y = y;

            if(yIt != intTransformNames.end()){
                t.isYtransform = true;
                t.yIndex = std::distance(intTransformNames.begin(), yIt);
            } else {
                t.isYtransform = false;
                t.yIndex = 0;
            }

            level[y][x] = t;
        }
    }
}

// ============================================
// === Objects & Object Identifiers Loaders ===
// ============================================

// Instantiates spriteNames and sprites from json
// Ignores empty files

void levels::loadSprites(const std::string& path){
    spriteNames.clear();
    sprites.clear();

    nlohmann::json spriteData;

    std::ifstream f(path + "/sprites.json");
    if(!f.is_open()) return;
    f >> spriteData;

    for (auto it = spriteData.begin(); it != spriteData.end(); it++){
        const std::string& name = it.key();
        intTransformNames.push_back(name);

        sprites::spriteDef chain;

        sprites::loadSprite(name, spriteData, chain.layers);
        sprites.push_back(chain);
    }
}

// Instantiates colorTransformNames and colorTransforms from json
// Ignores empty files

void levels::loadColorTransforms(const std::string& path){
    colorTransformNames.clear();
    colorTransforms.clear();

    nlohmann::json colorTransformData;

    std::ifstream f(path + "/color_transforms.json");
    if(!f.is_open()) return;
    f >> colorTransformData;

    for (auto it = colorTransformData.begin(); it != colorTransformData.end(); it++){
        const std::string& name = it.key();
        colorTransformNames.push_back(name);

        transform_chains::colorTransformDef chain;

        transform_loader::loadColorChain(name, colorTransformData, chain.transform);
        colorTransforms.push_back(chain);
    }
}

// Instantiates intTransformNames and intTransforms from json
// Ignores empty files

void levels::loadIntTransforms(const std::string& path){
    intTransformNames.clear();
    intTransforms.clear();

    nlohmann::json intTransformData;

    std::ifstream f(path + "/int_transforms.json");
    if(!f.is_open()) return;
    f >> intTransformData;

    for (auto it = intTransformData.begin(); it != intTransformData.end(); it++){
        const std::string& name = it.key();
        intTransformNames.push_back(name);

        transform_chains::intTransformDef chain;

        transform_loader::loadIntChain(name, intTransformData, chain.transform);
        intTransforms.push_back(chain);
    }
}

// Instantiates colorNames and colors from json
// Ignores empty files

void levels::loadColors(const std::string& path){
    colorNames.clear();
    colors.clear();

    nlohmann::json colorData;

    std::ifstream f(path + "/colors.json");
    if(!f.is_open()) return;
    f >> colorData;

    for (auto it = colorData.begin(); it != colorData.end(); ++it){
        const std::string& name = it.key();
        colorNames.push_back(name);

        SDL_Color c{0,0,0,255};

        if (it.value().is_object()) {
            auto obj = it.value();
            c.r = obj.value("r", 0);
            c.g = obj.value("g", 0);
            c.b = obj.value("b", 0);
            c.a = obj.value("a", 255);
        }

        colors.push_back(c);
    }
}