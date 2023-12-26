#pragma once
#include "GLCore/Core/Core.hpp"
#include "GLCore/Extension/Extension.hpp"


using namespace GLCore;

class ExampleLayer : public Layer
{
private:
private:
	Extension::Shaders::Shader* cubeShader;
	std::unique_ptr<Extension::Primitives::VBO> cubeVbo;
	std::unique_ptr<Extension::Primitives::VAO> cubeVao;

	std::vector<float> cubeVertices = {
		// Front face (Green)
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Vertex 1
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Vertex 3
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Vertex 4
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Vertex 5
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Vertex 6

		// Back face (Red)
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Vertex 2
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Vertex 3
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Vertex 4
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Vertex 5
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Vertex 6

		// Left face (Blue)
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // Vertex 1
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Vertex 2
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Vertex 3
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Vertex 4
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // Vertex 5
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // Vertex 6

		// Right face (Yellow)
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, // Vertex 1
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // Vertex 2
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // Vertex 3
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // Vertex 4
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, // Vertex 5
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, // Vertex 6

		 // Bottom face (Cyan)
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // Vertex 1
		  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // Vertex 2
		  0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // Vertex 3
		  0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // Vertex 4
		 -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // Vertex 5
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // Vertex 6

		 // Top face (Magenta)
		 -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, // Vertex 1
		  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, // Vertex 2
		  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, // Vertex 3
		  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, // Vertex 4
		 -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, // Vertex 5
		 -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f  // Vertex 6
	};

	Extension::Shaders::Shader* axisShader;
	std::unique_ptr<Extension::Primitives::VBO> axisVbo;
	std::unique_ptr<Extension::Primitives::VAO> axisVao;
	std::vector<float> axisVertices = {
		//X Axis (Red)
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		//Y Axis (Green)
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		//Z Axis (Blue)
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};


	Extension::Shaders::ComputeShader* computeShader;
	std::unique_ptr<Extension::Primitives::SSBO> points_ssbo;

	struct Point {
		glm::vec2 pos;
		glm::vec2 color;
	};

	std::vector<Point> points = {
		{glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec2(2.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
		{glm::vec2(3.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		// ... add more points as needed
	};

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float yaw = -90.f;
	float pitch = 0;
	float initFOV = 45.0f;
	
	std::unique_ptr<Extension::Cameras::PerspectiveCamera> camera;

public:
	ExampleLayer() : Layer("ExampleLayer")
	{
	}
	virtual ~ExampleLayer()
	{

	}

	virtual void onAttach() override
	{
		Extension::Cameras::PerspectiveCameraProps cameraProps(
			glm::vec3(0.0f, 0.0f, 3.0f),
			-90.0f,
			0.0f,
			glm::vec3(0.0f, 1.0f, 0.0f),
			45.0f,
			0.1f,
			100.0f
		);
		cameraProps.enableFOVWithScroll();
		cameraProps.enableMovementWithKeys();
		cameraProps.enableRotateWithRightClick();
		cameraProps.enableRotateWithKeys();
		camera = std::make_unique<Extension::Cameras::PerspectiveCamera>(cameraProps);

		WindowProps& props = Application::get().getWindow().getProps();

		/*Cube*/
		cubeShader = &Extension::AssetPool::getShader("Cube");
		cubeVao = std::make_unique<Extension::Primitives::VAO>();
		cubeVbo = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, &cubeVertices);
		cubeVao->addVertexAttributeFloat(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		cubeVao->addVertexAttributeFloat(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		cubeVao->disableAttributes();

		/*Axis*/
		axisShader = &Extension::AssetPool::getShader("Axis");
		axisVao = std::make_unique<Extension::Primitives::VAO>();
		axisVbo = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, &axisVertices);
		axisVao->addVertexAttributeFloat(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		axisVao->disableAttributes();

		//ComputeShader Testing
		computeShader = &Extension::AssetPool::getComputeShader("Point");
		points_ssbo = std::make_unique<Extension::Primitives::SSBO>(GL_STATIC_DRAW, &points);		
	}
	virtual void onDetach() override
	{
	}
	virtual void onUpdate(const GLCore::TimeStep &ts) override
	{
		points_ssbo->bindAt(1);
		computeShader->use();
		computeShader->dispatch(glm::ivec3(points.size(), 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		points_ssbo->unbind();
		computeShader->detach();

		camera->onUpdate(ts, Extension::Cameras::PerspectiveCameraOptions::ROTATE_USING_PITCH_YAW);

		/*Cube*/
		cubeShader->use();
		cubeShader->uploadMat4f("VP", camera->getViewProjection());
		cubeVao->bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		cubeVao->unbind();
		cubeShader->detach();

		/*Axis*/
		axisShader->use();
		axisShader->uploadMat4f("VP", camera->getViewProjection());
		axisVao->bind();

		glDrawArrays(GL_LINES, 0, 6);

		axisVao->unbind();
		axisShader->detach();
	}
	virtual void onImguiUpdate(const GLCore::TimeStep &ts) override
	{
		ImGui::ShowDemoWindow();
	}

private:
};