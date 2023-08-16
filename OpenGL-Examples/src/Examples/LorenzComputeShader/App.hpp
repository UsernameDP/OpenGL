#pragma once
#include "GLCore.hpp"
#include "Layer_ImGui.hpp"
#include "AssetPoolINIT.hpp"

#include "LorenzLayer.hpp"

using namespace GLCore;

class Lorenz_App : public Application {
public:
    Lorenz_App(const std::string& name,
        uint32_t width,
        uint32_t height,
        glm::vec4 backgroundColor) : Application(name, width, height, backgroundColor) {
    }

    void init() override {
        setImGuiLayer(std::make_unique<Layer_ImGui>());
        initializeAssetPool(std::make_unique<AssetPoolINIT>());
        pushLayer(new LorenzLayer());
    }
};