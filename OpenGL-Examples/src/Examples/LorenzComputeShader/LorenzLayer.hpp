#pragma once
#include "GLCoreLayer.hpp"
#include "GLCoreComputeExtensions.hpp"

using namespace GLCore;

class LorenzLayer : public Layer {
private:
	struct Point {
		glm::vec4 position;
		glm::vec4 color;
	};

	Shaders::Shader* computeShader = nullptr;
	Primitives::SSBO* lorenz_buffer = nullptr;

	//Points
	const size_t number_of_points = 1;
	std::vector<Point> points;

	//Uniforms : 
	const float dt = 0.01f;
	const float a = 10.0f;
	const float b = 28.0f;
	const float c = 8.0f / 3.0f;

public:
	LorenzLayer() : Layer("Lorenz") {};
	
	void onAttach() override {
		//Populate lorenz_buffer with data
		points = std::vector<Point>(number_of_points);

		const float gap = 0.01f;
		for (int i = 0; i < number_of_points; i++) {
			points[i].position = glm::vec4(gap * (i + 1), gap * (i + 1), gap * (i + 1), 0.0f);
			points[i].color = glm::vec4(i, 0.0f, 0.0f, 0.0f);

		}
		//Create ComputeShader
		computeShader = new Shaders::ComputeShader("LorenzShader",
			"OpenGL-Examples\\src\\Examples\\LorenzComputeShader\\assets\\LorenzShader.comp"
		);

		//Create SSBO
		lorenz_buffer = new Primitives::SSBO(GL_STATIC_DRAW, number_of_points, &points);
	}

	void onDetach() override {
		delete computeShader;
		delete lorenz_buffer;
	}

	void onUpdate(const TimeStep& ts) override {
		//bind SSBO
		lorenz_buffer->bind(0);
		//use the computeShader
		computeShader->use();
		//upload uniforms : 
		computeShader->uploadFloat("dt", dt );
		computeShader->uploadFloat("a", a);
		computeShader->uploadFloat("b", b);
		computeShader->uploadFloat("c", c);
		//dispath computations
		Shaders::ComputeShader::dispatchComputeShader(glm::vec3(number_of_points, 1, 1));
		Shaders::ComputeShader::runWithMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
		//unbind all
		lorenz_buffer->unbind();
		computeShader->detach();

		// get ssbo data
		lorenz_buffer->readDataTo(&points);

		printPoints();
	}

	void onImguiUpdate(const TimeStep& ts) override {};


	void printPoints() {
		std::cout << "Points Vector:\n";
		for (const Point& point : points) {
			std::cout << "Position: (" << point.position.x << ", "
				<< point.position.y << ", " << point.position.z << ", " << point.position.w << "), "
				<< "Color: (" << point.color.x << ", "
				<< point.color.y << ", " << point.color.z << ", " << point.color.w << ")\n";
		}
		std::cout << std::endl;
	}
};