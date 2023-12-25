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
	std::unique_ptr<Extension::Primitives::VertexAttributes> cubeVertexAttributes;

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
	std::unique_ptr<Extension::Primitives::VertexAttributes> axisVertexAttributes;
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
	std::unique_ptr<Extension::Primitives::SSBO> ssbo;

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
		//Extension::Cameras::PerspectiveCameraProps cameraProps(
		//	glm::vec3(0.0f, 0.0f, 3.0f),
		//	0.0f,
		//	-90.0f,
		//	glm::vec3(0.0f, 1.0f, 0.0f),
		//	45.0f,
		//	0.1f,
		//	100.0f
		//);
		Extension::Cameras::PerspectiveCameraProps cameraProps(
			10.0f,
			0.0f,
			90.0f,
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0, 1.0f, 0.0f),
			45.0f,
			0.1f,
			100.0f
		);
		cameraProps.enableFOVWithScroll();
		//cameraProps.enableMovementWithKeys();
		//cameraProps.enableRotateWithRightClick();
		//cameraProps.enableRotateWithKeys();
		cameraProps.enableRotateAboutWithKeys();
		cameraProps.setCameraSpeedFactor(50.0f);
		cameraProps.setMouseSensitivity(0.2f);
		camera = std::make_unique<Extension::Cameras::PerspectiveCamera>(cameraProps);

		WindowProps& props = Application::get().getWindow().getProps();

		//Camera
		model = glm::mat4(1.0f);
		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);

		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // (model matrix, rotation angle rad, axis of rotation)
		//projection = glm::perspective(glm::radians(initFOV), (float)props.getWidth() / (float)props.getHeight(), 0.1f, 100.0f); // (view angle, window width to height ratio, min visible dist, max visible dist)
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		//VertexPipelineShader Testing
		cubeShader = &Extension::AssetPool::getShader("Cube");

		cubeVertexAttributes = std::make_unique<Extension::Primitives::VertexAttributes>();
		cubeVertexAttributes->addVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);					// Position
		cubeVertexAttributes->addVertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // Color

		cubeVao = std::make_unique<Extension::Primitives::VAO>();
		cubeVbo = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, &cubeVertices);

		cubeVertexAttributes->setAttributes();

		axisShader = &Extension::AssetPool::getShader("Axis");

		axisVertexAttributes = std::make_unique<Extension::Primitives::VertexAttributes>();
		axisVertexAttributes->addVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);					// Position

		axisVao = std::make_unique<Extension::Primitives::VAO>();
		axisVbo = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, &axisVertices);

		axisVertexAttributes->setAttributes();

		//ComputeShader Testing
		computeShader = &Extension::AssetPool::getComputeShader("Point");
		ssbo = std::make_unique<Extension::Primitives::SSBO>(GL_STATIC_DRAW, &points);
	}
	virtual void onDetach() override
	{
	}
	virtual void onUpdate(const GLCore::TimeStep &ts) override
	{
		ssbo->bindAt(1);
		computeShader->use();
		computeShader->dispatch(glm::ivec3(points.size(), 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		ssbo->unbind();
		computeShader->detach();

		//ssbo->readDataTo(&points);
		//for (const Point& point : points) {
		//	std::cout << "Position: (" << point.pos.x << ", " << point.pos.y  << "), "
		//		<< "Color: (" << point.color.r << ", " << point.color.g << ")" << std::endl;
		//}
		
		/*
		//Coordinate Systems
		model = glm::rotate(model, ts.getDeltaSeconds() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		*/

		/*
		//(Camera) Rotating about Target
		const float radius = 10.0f;
		glm::vec3 cameraPos =  glm::vec3( glm::sin(ts.getSeconds()) * radius, 5.0f,  glm::cos(ts.getSeconds()) * radius);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		view = glm::lookAt(cameraPos, cameraTarget, up);
		*/

		/*
		//(Camera) Rotationg using pitch yaw 
		Application& app = Application::get();
		WindowProps& props = app.getWindow().getProps();
		const float cameraSpeed = 2.5f * ts.getDeltaSeconds(); //cameraspeed accounted for by dt
		if (app.getKeyPressed(GLFW_KEY_W)) {
			cameraPos += cameraFront * cameraSpeed;
		}
		if (app.getKeyPressed(GLFW_KEY_S)) {
			cameraPos -= cameraFront * cameraSpeed;
		}
		if (app.getKeyPressed(GLFW_KEY_D)) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (app.getKeyPressed(GLFW_KEY_A)) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		//const float sensitivity = 0.1f;
		//float deltaYaw = props.getMousePosDeltaX(); // X angle
		//float deltaPitch = props.getMousePosDeltaY(); // Y angle

		//yaw += deltaYaw * sensitivity;
		//pitch -= deltaPitch * sensitivity;

		//if (pitch > 89.0f)
		//	pitch = 89.0f;
		//if (pitch < -89.0f)
		//	pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);

		float scrollY = props.getScrollY();
		float fov = initFOV - scrollY;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 45.0f)
			fov = 45.0f;

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		projection = glm::perspective(glm::radians(fov), (float)props.getWidth() / (float)props.getHeight(), 0.1f, 100.0f);
		*/
	

		camera->onUpdate(ts, Extension::Cameras::PerspectiveCameraOptions::ROTATE_USING_CAMERA_TARGET);
		//camera->onUpdate(ts, Extension::Cameras::PerspectiveCameraOptions::ROTATE_USING_PITCH_YAW);

		/*Cube*/
		cubeShader->use();
		cubeShader->uploadMat4f("model", model);
		cubeShader->uploadMat4f("view_projection", camera->getViewProjection());
		cubeVao->bind();
		cubeVertexAttributes->enableAttributes();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		cubeVertexAttributes->disableAttributes();
		cubeVao->unbind();
		cubeShader->detach();

		/*Axis*/
		axisShader->use();
		axisShader->uploadMat4f("view_projection", camera->getViewProjection());
		axisVao->bind();
		axisVertexAttributes->enableAttributes();

		glDrawArrays(GL_LINES, 0, 6);

		axisVertexAttributes->disableAttributes();
		axisVao->unbind();
		axisShader->detach();
	}
	virtual void onImguiUpdate(const GLCore::TimeStep &ts) override
	{
		ImGui::ShowDemoWindow();
	}

private:
};