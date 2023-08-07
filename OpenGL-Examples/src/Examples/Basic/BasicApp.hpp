#pragma once
#include "GLCore.hpp"
#include "BasicImGuiLayer.hpp"
#include "BasicAssetPoolINIT.hpp"
#include "BasicLayer.hpp"

using namespace GLCore;

class BasicApp : public Application {
public:
    BasicApp(const std::string& name,
        uint32_t width,
        uint32_t height,
        glm::vec4 backgroundColor) : Application(name, width, height, backgroundColor) {
    }

    void init() override {
        setImGuiLayer(std::make_unique<BasicImGuiLayer>());
        initializeAssetPool(std::make_unique<BasicAssetPoolINIT>());
        pushLayer(new BasicLayer());
    }
};