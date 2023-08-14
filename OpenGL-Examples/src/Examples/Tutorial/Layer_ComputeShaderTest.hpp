#pragma once
#include "GLCore.hpp"
#include "GLCoreLayer.hpp"
#include "GLCoreComputeExtensions.hpp"

using namespace GLCore;

class Layer_ComputeShaderTest : public Layer {
private:
	Shaders::Shader* computeShader = nullptr;
	Primitives::SSBO ssboInput1;
	Primitives::SSBO ssboInput2;
	Primitives::SSBO ssboOutput;
	
	const int arraySize = 10;

	std::vector<float> inputArr1;
	std::vector<float> inputArr2;
	std::vector<float> outputArr;
	

public:
	Layer_ComputeShaderTest() : Layer("ComputeShaderTest") {}
	
	void onAttach() override {
	inputArr1 = std::vector<float>(arraySize);
		inputArr2 = std::vector<float>(arraySize);
		outputArr = std::vector<float>(arraySize);

		for (int i = 0; i < arraySize; i++) {
			inputArr1[i] = static_cast<float>(i);
			inputArr2[i] = static_cast<float>(i);
		}



		computeShader = new Shaders::ComputeShader(
			"ComputeShaderTest",
			"OpenGL-Examples\\assets\\shaders\\ComputeTest.comp",
			glm::vec3 (256, 1, 1),
			GL_SHADER_STORAGE_BARRIER_BIT
			);
		ssboInput1 = Primitives::SSBO(GL_STATIC_DRAW, inputArr1.size(), &inputArr1);
		ssboInput1.create();
		ssboInput1.unbind();
		ssboInput2 = Primitives::SSBO(GL_STATIC_DRAW, inputArr2.size(), &inputArr2);
		ssboInput2.create();
		ssboInput2.unbind();
		ssboOutput = Primitives::SSBO(GL_STATIC_DRAW, outputArr.size());
		ssboOutput.create();
		ssboOutput.unbind();
	
		ssboInput1.bind(0);
		ssboInput2.bind(1);
		ssboOutput.bind(2);
		computeShader->use();


		exd::printVector(outputArr);

		computeShader->detach();
		ssboInput1.unbind();
		ssboInput2.unbind();
		ssboOutput.unbind();
	}
	void onDetach() override {
		ssboInput1.destroy();
		ssboInput2.destroy();
		ssboOutput.destroy();

		delete computeShader;
	}
	void onUpdate(const TimeStep& ts) override {

	}
	void onImguiUpdate(const TimeStep& ts) override {

	}
	
};