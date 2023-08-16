#include "GLCore.hpp"
#include "GLCoreLayer.hpp"
#include "GLCoreComputeExtensions.hpp"

using namespace GLCore;

class Layer_ComputeShaderMultiple : public Layer {
private:
    Shaders::Shader* computeShader = nullptr;
    Primitives::SSBO* ssbo = nullptr;

    const size_t arraySize = 5;

public:
    Layer_ComputeShaderMultiple() : Layer("ComputeShaderStruct") {}

    void onAttach() override {
        // Create ComputeShader
        computeShader = new Shaders::ComputeShader(
            "ComputeShaderTest",
            "OpenGL-Examples\\assets\\shaders\\ComputeTestMultiple.comp"
        );

        // Initialize float array
        std::vector<float> floatArray(arraySize);
        for (int i = 0; i < arraySize; i++) {
            floatArray[i] = static_cast<float>(i);
        }

        // Initialize int array
        std::vector<int> intArray(arraySize);
        for (int i = 0; i < arraySize; i++) {
            intArray[i] = i;
        }

        const size_t totalArraySize = arraySize + arraySize;
        const size_t totalArraySize_DT = totalArraySize * (sizeof(float) + sizeof(int));

        // Create SSBO
        ssbo = new Primitives::SSBO(GL_DYNAMIC_DRAW, totalArraySize, totalArraySize_DT);

        ssbo->resetOffset();
        ssbo->uploadSubData(&floatArray);
        ssbo->uploadSubData(&intArray);
        ssbo->resetOffset();

        // Run ComputeShader
        ssbo->bind(0);
        computeShader->use();
        Shaders::ComputeShader::dispatchComputeShader(glm::ivec3(arraySize, 1, 1));
        Shaders::ComputeShader::runWithMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        ssbo->unbind();
        computeShader->detach();

        ssbo->readDataTo(&floatArray, 0, 4);
        ssbo->readDataTo(&intArray, 5, 9);

        exd::printVector(floatArray);
        exd::printVector(intArray);

    }

    void onDetach() override {
        delete ssbo;
        delete computeShader;
    }

    void onUpdate(const TimeStep& ts) override {}

    void onImguiUpdate(const TimeStep& ts) override {}
};
