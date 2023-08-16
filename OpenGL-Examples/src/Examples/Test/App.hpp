#pragma once
#include "GLCore.hpp"
#include "Layer_ImGui.hpp"
#include "AssetPoolINIT.hpp"

#include "Layer_ComputeShaderMultiple.hpp"
#include "Layer_ComputeShaderStruct.hpp"

using namespace GLCore;

class Test_App : public Application {
public:
    Test_App(const std::string& name,
        uint32_t width,
        uint32_t height,
        glm::vec4 backgroundColor) : Application(name, width, height, backgroundColor) {
    }

    void init() override {
        setImGuiLayer(std::make_unique<Layer_ImGui>());
        initializeAssetPool(std::make_unique<AssetPoolINIT>());
        pushLayer(new Layer_ComputeShaderStruct());
    }
};