#pragma once
#include "GLCore.hpp"
#include "Layer_ImGui_Tutorial.hpp"
#include "Tutorial_AssetPoolINIT.hpp"
#include "Layer_Transformations.hpp"
#include "Layer_CoordinateSystems.hpp"
#include "Layer_CoordinateSystems2.h"

using namespace GLCore;

class Tutorial_App : public Application {
public:
    Tutorial_App(const std::string& name,
        uint32_t width,
        uint32_t height,
        glm::vec4 backgroundColor) : Application(name, width, height, backgroundColor) {
    }

    void init() override {
        setImGuiLayer(std::make_unique<Layer_ImGui_Tutorial>());
        initializeAssetPool(std::make_unique<Tutorial_AssetPoolINIT>());
        pushLayer(new Layer_CoordinateSystems2());
    }
};