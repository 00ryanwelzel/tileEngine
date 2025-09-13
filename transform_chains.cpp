#include "transform_chains.h"

using namespace std;
using namespace transform_functions;

namespace transform_chains{

    // === Templates Functions ===

    template<typename T>
    uint getFrames(const std::vector<T>& transformContainers){
        uint chainFrameTotal = 0;
        for(const auto& container : transformContainers){
            chainFrameTotal += container.frameTotal;
        }
        return chainFrameTotal;
    }

    template<typename Tin, typename Tout>
    Tout getCurrent(const std::vector<Tin>& transformContainers, const uint frame) {
        uint frameTraversal = frame % getFrames(transformContainers);

        while (true) {
            for (const auto& container : transformContainers) {
                if (frameTraversal >= container.frameTotal) {
                    frameTraversal -= container.frameTotal;
                    continue;
                }

                if (container.no_op){
                    return container.from;
                }

                if constexpr (std::is_same_v<Tout, SDL_Color> == 1) {
                    return transform_functions::transformColor(
                        container.from, 
                        container.to, 
                        frameTraversal, 
                        container.frameTotal, 
                        container._curveFunction
                    );
                } else {
                    return transform_functions::interpol<Tout>(
                        container.from, 
                        container.to, 
                        frameTraversal, 
                        container.frameTotal, 
                        container._curveFunction
                    );
                }
            }
        }
    }

    // === Templates Applications ===

    // getFrames()

    uint getColorChainFrames(const std::vector<color_transform>& transformContainers){
        return getFrames<color_transform>(transformContainers);
    }

    uint getIntChainFrames(const std::vector<int_transform>& transformContainers){
        return getFrames<int_transform>(transformContainers);
    }

    uint getUint8ChainFrames(const std::vector<Uint8_transform>& transformContainers){
        return getFrames<Uint8_transform>(transformContainers);
    }

    uint getFloatChainFrames(const std::vector<float_transform>& transformContainers){
        return getFrames<float_transform>(transformContainers);
    }

    // getCurrent()

    int getCurrentInt(const std::vector<int_transform>& transformContainers, const uint frame){
        return getCurrent<int_transform, int>(transformContainers, frame);
    }

    Uint8 getCurrentUint8(const std::vector<Uint8_transform>& transformContainers, const uint frame){
        return getCurrent<Uint8_transform, Uint8>(transformContainers, frame);
    }

    SDL_Color getCurrentColor(const std::vector<color_transform>& transformContainers, const uint frame){
        return getCurrent<color_transform, SDL_Color>(transformContainers, frame);
    }

    float getCurrentFloat(const std::vector<float_transform>& transformContainers, const uint frame){
        return getCurrent<float_transform, float>(transformContainers, frame);
    }

    // loadChain()

}
