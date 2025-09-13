#include "transform_functions.h"
#include "transform_chains.h"
#include "transform_loader.h"

#include "sprites.h"

#include "levels.h"

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <nlohmann/json.hpp>

using namespace std;
using namespace transform_functions;
using namespace transform_chains;
using namespace sprites;

nlohmann::json spriteData;
nlohmann::json colorData;
nlohmann::json intData;

const int w = 1280;
const int h = 1280;

int globalx = 0;
int globaly = 0;

const uint wtile = 32;
const uint htile = 32;
const uint xtile = 128;
const uint ytile = 128;

const SDL_Color cyan = SDL_Color{0x00, 0xFF, 0xFF, 0xFF};
const SDL_Color magenta = SDL_Color{0xFF, 0x00, 0xFF, 0xFF};
const SDL_Color testBackground = SDL_Color{0x00, 0x00, 0x00, 0xFF};

// 09 11 25 5 hours

std::vector<sprites::spriteLayer> testSprite;
std::vector<transform_chains::color_transform> testChain;
std::vector<transform_chains::int_transform> testChain2;

int numdraws = 0;

Uint32 fpsLastTime = 0;  // Time at last FPS update
Uint32 fpsFrames = 0;    // Frame count since last update
float currentFPS = 0.0f;

void updateFPS() {
    Uint32 currentTime = SDL_GetTicks();  // ms since SDL_Init
    fpsFrames++;

    if (currentTime > fpsLastTime + 1000) {
        currentFPS = (fpsFrames * 1000.0f) / (currentTime - fpsLastTime);
        fpsLastTime = currentTime;
        fpsFrames = 0;

        std::cout << "FPS: " << currentFPS << std::endl;
    }
}


int main(){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);


    SDL_Window* window = SDL_CreateWindow(
        "Fortnite 2 Electic Boogaloo: Directed by Michael Bay",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_SHOWN
    );

    std::ifstream f("level1/sprites.json");
    f >> spriteData;
    std::ifstream f2("level1/color_transforms.json");
    f2 >> colorData;
    std::ifstream f3("level1/int_transforms.json");
    f3 >> intData;

    sprites::loadSprite("EPICSMILEYFACE", spriteData, testSprite);
    transform_loader::loadColorChain("CYAN_TO_MAGENTA_LOOP", colorData, testChain);
    transform_loader::loadIntChain("TEST_TRANSFORM", intData, testChain2);

    // whatever the fuck renderer does
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;
    bool running = true;

    uint frame = 0;
    uint frameTotal = 120;
    //uint frameTotal = 128;

    levels l;
    l.loadLevel("level1");

    while(running){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) running = false;
            else if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_w:
                        globaly++;
                        break;
                    case SDLK_a:
                        globalx++;
                        break;
                    case SDLK_s:
                        globaly--;
                        break;
                    case SDLK_d:
                        globalx--;
                        break;
                
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        /*draw_functions::draw(
            renderer, 
            transform_chains::getCurrentColor(loop, frame),
            transform_chains::getCurrentColor(loop, frame),
            testBackground, 
            transform_chains::getCurrentInt(loop2, frame), 
            transform_chains::getCurrentInt(loop3, frame), 
            transform_chains::getCurrentInt(loop2, frame), 
            transform_chains::getCurrentInt(loop3, frame), 
            style::BORDER_FILL
        );*/

        //sprites::drawSprite(
        //    renderer,
        //);

        //sprites::drawSprite(
        //    renderer,
        //    testSprite,
        //    cyan,
        //    transform_chains::getCurrentColor(testChain, frame),
        //    testBackground,
        //    globalx + transform_chains::getCurrentInt(testChain2, frame),
        //    globaly + transform_chains::getCurrentInt(testChain2, frame),
        //    transform_chains::getCurrentInt(testChain2, frame),
        //    transform_chains::getCurrentInt(testChain2, frame)
        //);

        l.drawLevel(renderer, frame, globalx, globaly, 32, 32);

        SDL_RenderPresent(renderer);
        updateFPS();

        frame = ((frame + 1) % 120);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
