#include "transform_loader.h"

using namespace std;
using namespace transform_functions;
using namespace transform_chains;

namespace transform_loader{

    // ==================================================
    // === Implementation For color_transform Structs ===
    // ==================================================
 
    void loadColorChain(
        const std::string& chainName, 
        const nlohmann::json& chains, 
        std::vector<transform_chains::color_transform>& outChain
    ){
        outChain.clear();

        if (!chains.contains(chainName)){
            std::cerr << "Transform chain not found: " << chainName << std::endl;
            return;
        }

        const auto& chainArray = chains.at(chainName);

        if (!chainArray.is_array()){
            std::cerr << "Chain " << chainName << " is not an array.\n";
            return;
        }

        
        for (const auto& j : chainArray){
            transform_chains::color_transform t;

            const auto& fromJson = j.at("from");
            const auto& toJson   = j.at("to");

            t.from.r = fromJson.at("r").get<Uint8>();
            t.from.g = fromJson.at("g").get<Uint8>();
            t.from.b = fromJson.at("b").get<Uint8>();
            t.from.a = fromJson.at("a").get<Uint8>();

            t.to.r = toJson.at("r").get<Uint8>();
            t.to.g = toJson.at("g").get<Uint8>();
            t.to.b = toJson.at("b").get<Uint8>();
            t.to.a = toJson.at("a").get<Uint8>();

            j.at("frameTotal").get_to(t.frameTotal);
            j.at("no_op").get_to(t.no_op);

            std::string curveName = j.at("curveFunction").get<std::string>();
            t._curveFunction = transform_functions::stringToCurveFunction(curveName);

            outChain.push_back(std::move(t));
        }
    }

    // ================================================
    // === Implementation For int_transform Structs ===
    // ================================================

    void loadIntChain(
        const std::string& chainName, 
        const nlohmann::json& chains, 
        std::vector<transform_chains::int_transform>& outChain
    ){
        outChain.clear();

        if (!chains.contains(chainName)){
            std::cerr << "Transform chain not found: " << chainName << std::endl;
            return;
        }

        const auto& chainArray = chains.at(chainName);

        if (!chainArray.is_array()){
            std::cerr << "Chain " << chainName << " is not an array.\n";
            return;
        }

        for (const auto& j : chainArray){
            transform_chains::int_transform t;

            j.at("from").get_to(t.from);
            j.at("to").get_to(t.to);

            j.at("frameTotal").get_to(t.frameTotal);
            j.at("no_op").get_to(t.no_op);

            std::string curveName = j.at("curveFunction").get<std::string>();
            t._curveFunction = transform_functions::stringToCurveFunction(curveName);

            outChain.push_back(std::move(t));
        }
    }

    // ==================================================
    // === Implementation For Uint8_transform Structs ===
    // ==================================================

    void loadUint8Chain(
        const std::string& chainName, 
        const nlohmann::json& chains, 
        std::vector<transform_chains::Uint8_transform>& outChain
    ){
        outChain.clear();

        if (!chains.contains(chainName)){
            std::cerr << "Transform chain not found: " << chainName << std::endl;
            return;
        }

        const auto& chainArray = chains.at(chainName);

        if (!chainArray.is_array()){
            std::cerr << "Chain " << chainName << " is not an array.\n";
            return;
        }

        for (const auto& j : chainArray){
            transform_chains::Uint8_transform t;

            j.at("from").get_to(t.from);
            j.at("to").get_to(t.to);

            j.at("frameTotal").get_to(t.frameTotal);
            j.at("no_op").get_to(t.no_op);

            std::string curveName = j.at("curveFunction").get<std::string>();
            t._curveFunction = transform_functions::stringToCurveFunction(curveName);

            outChain.push_back(std::move(t));
        }
    }

    // ==================================================
    // === Implementation For float_transform Structs ===
    // ==================================================

    void loadFloatChain(
        const std::string& chainName, 
        const nlohmann::json& chains, 
        std::vector<transform_chains::float_transform>& outChain
    ){
        outChain.clear();

        if (!chains.contains(chainName)){
            std::cerr << "Transform chain not found: " << chainName << std::endl;
            return;
        }

        const auto& chainArray = chains.at(chainName);

        if (!chainArray.is_array()){
            std::cerr << "Chain " << chainName << " is not an array.\n";
            return;
        }

        for (const auto& j : chainArray){
            transform_chains::float_transform t;

            j.at("from").get_to(t.from);
            j.at("to").get_to(t.to);

            j.at("frameTotal").get_to(t.frameTotal);
            j.at("no_op").get_to(t.no_op);

            std::string curveName = j.at("curveFunction").get<std::string>();
            t._curveFunction = transform_functions::stringToCurveFunction(curveName);

            outChain.push_back(std::move(t));
        }
    }

    // === //
}
