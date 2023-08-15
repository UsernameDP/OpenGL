#pragma once
#include "GLCore.hpp"
#include "GLCoreLayer.hpp"
#include "GLCoreComputeExtensions.hpp"

using namespace GLCore;

class Layer_ComputeShaderTest : public Layer {
private:
	Shaders::Shader* computeShader = nullptr;
	Primitives::SSBO ssbo;
	Primitives::SSBO ssbo2;
	
	const int arraySize = 10;

	std::vector<float> data;
	std::vector<float> data2;
	

public:
	Layer_ComputeShaderTest() : Layer("ComputeShaderTest") {}
	
	void onAttach() override {
		data = std::vector<float>(arraySize);
		data2 = std::vector<float>(arraySize);
		
		for (int i = 0; i < arraySize; i++) {
			data[i] = static_cast<float>(i);
			data2[i] = static_cast<float>(i * 2);
		}

		std::vector<float> test(arraySize);
		for (int i = 0; i < arraySize; i++) {
			test[i] = data[i] + data2[i];
		}

		//Create ComputeShader
		computeShader = new Shaders::ComputeShader(
			"ComputeShaderTest",
			"OpenGL-Examples\\assets\\shaders\\ComputeTest.comp"
			);

		//Create SSBOs
		ssbo = Primitives::SSBO(GL_STATIC_DRAW, arraySize, &data);

		//Run ComputeShader
		ssbo.bind(0);
		computeShader->use();
		Shaders::ComputeShader::dispatchComputeShader(glm::ivec3(arraySize, 1, 1));
		Shaders::ComputeShader::runWithMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		ssbo.unbind();
		ssbo2.unbind();
		computeShader->detach();

		ssbo.readDataTo(&data);
		exd::printVector(data);
	}
	void onDetach() override {
		ssbo.destroy();
		ssbo2.destroy();

		delete computeShader;
	}
	void onUpdate(const TimeStep& ts) override {

	}
	void onImguiUpdate(const TimeStep& ts) override {

	}
	
};