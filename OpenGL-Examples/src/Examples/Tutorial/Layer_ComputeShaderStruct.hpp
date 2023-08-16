#pragma once
#include "GLCore.hpp"
#include "GLCoreLayer.hpp"
#include "GLCoreComputeExtensions.hpp"

using namespace GLCore;

class Layer_ComputeShaderStruct : public Layer {
private:
    struct MyStruct {
        glm::vec4 position;
        glm::vec4 direction;
    };

    Shaders::Shader* computeShader = nullptr;
    Primitives::SSBO* ssbo;

    const int arraySize = 5;

    std::vector<MyStruct> data;

public:
    Layer_ComputeShaderStruct() : Layer("ComputeShaderStruct") {}

    void onAttach() override {
        data = std::vector<MyStruct>(arraySize);

        for (int i = 0; i < arraySize; i++) {
            data[i].position = glm::vec4(i, i, i, 1.0f);
            data[i].direction = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f); // Example direction
        }

        // Create ComputeShader
        computeShader = new Shaders::ComputeShader(
            "ComputeShaderTest",
            "OpenGL-Examples\\assets\\shaders\\ComputeTest.comp"
        );

        // Create SSBO
        ssbo = new Primitives::SSBO(GL_STATIC_DRAW, arraySize, &data);

        // Run ComputeShader
        ssbo->bind(0);
        computeShader->use();
        Shaders::ComputeShader::dispatchComputeShader(glm::ivec3(arraySize, 1, 1));
        Shaders::ComputeShader::runWithMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        ssbo->unbind();
        computeShader->detach();

        // Read modified data back
        ssbo->readDataTo(&data);

        for (const MyStruct& myStruct : data) {
            std::cout << "Updated Position: (" << myStruct.position.x << ", "
                << myStruct.position.y << ", " << myStruct.position.z << ", " << myStruct.position.w << ")" << std::endl;
            std::cout << "Updated Direction: (" << myStruct.direction.x << ", "
                << myStruct.direction.y << ", " << myStruct.direction.z << ", " << myStruct.direction.w << ")" << std::endl;
        }
    }

    void onDetach() override {
        delete ssbo;
        delete computeShader;
    }

    void onUpdate(const TimeStep& ts) override {}

    void onImguiUpdate(const TimeStep& ts) override {}
};
