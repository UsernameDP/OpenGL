#pragma once
#include "GLCoreLayer.hpp"
#include "GLCoreGraphicsExtensions.hpp"
#include <cmath>

using namespace GLCore;

class Layer_Camera : public Layer {
private:
	Shaders::Shader* shader = nullptr;
	Primitives::Texture* texture1 = nullptr;
	Primitives::Texture* texture2 = nullptr;

	std::shared_ptr<Primitives::VertexAttributes> vertexAttributes = nullptr;
	std::unique_ptr<Primitives::VertexPipeline> vertexPipeline = nullptr;
private:
	const int POS_SIZE = 3;
	const int TEX_SIZE = 2;
	const int VERTEX_SIZE = POS_SIZE + TEX_SIZE;

	std::vector<float> vertices = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//Walk Around : 
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	//Look Around :
	float yaw = -90.0f; //x mouse delta 
	float pitch = -45.0f; //y mouse delta
	const float mouseSensitivity = 0.1f;

public:
	Layer_Camera() : Layer("Camera") {};

	void onAttach() override {
		shader = util::AssetPool::getShader("CubeShader");

		vertexAttributes = Primitives::VertexAttributes::create();
		vertexAttributes->addVertexAttribute(0, POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)0);
		vertexAttributes->addVertexAttribute(1, TEX_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)((POS_SIZE) * sizeof(float)));

		vertexPipeline = Primitives::VertexPipeline::create();
		vertexPipeline->setVBO(GL_STATIC_DRAW, vertices.size(), &vertices);
		vertexPipeline->setVAO();
		vertexPipeline->setVertexAttributes(vertexAttributes);
		vertexPipeline->configure();

		texture1 = util::AssetPool::getTexture("OpenGL-Examples/assets/textures/gears.png");
		texture2 = util::AssetPool::getTexture("OpenGL-Examples/assets/textures/sky.jpg");

	}
	void onDetach() override {

	}
	void onUpdate(const TimeStep& ts) override {
		// create transformations
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		//Rotate
		//Gram-Schmidth method
		/*
		glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0f); //coords of where camera is
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); //coords of where camera is looking at
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); //getting direction of target relative to the cameraPos
		
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // unit y vector
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); //taking cross product gets a vector orthogonal to both vectors https://learnopengl.com/Getting-started/Transformations for more information
		
		const float rad = 10.0f;

		float camX = sin(ts) * rad;
		float camZ = cos(ts) * rad;

		glm::vec3 cameraPos = glm::vec3(camX, 0.0, camZ);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		view = glm::lookAt(cameraPos, cameraTarget, up); 
		*/

		//Walk Around
		/*
		deltaTime = ts - lastFrame;
		lastFrame = ts;

		float cameraSpeed = 2.5f * deltaTime;

		if (Application::getKey(GLFW_KEY_W, true)) {
			cameraPos += cameraSpeed * cameraFront;
		}
		if (Application::getKey(GLFW_KEY_S, true)) {
			cameraPos -= cameraSpeed * cameraFront;
		}
		if (Application::getKey(GLFW_KEY_D, true)) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (Application::getKey(GLFW_KEY_A, true)) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); //cameraPos + cameraFront = cameraTarget
		*/

		//Walk Around & Look around
		float cameraSpeed = 2.5f * ts.getDeltaSeconds();

		if (Application::getKey(GLFW_KEY_W, true)) {
			cameraPos += cameraSpeed * cameraFront;
		}
		if (Application::getKey(GLFW_KEY_S, true)) {
			cameraPos -= cameraSpeed * cameraFront;
		}
		if (Application::getKey(GLFW_KEY_D, true)) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (Application::getKey(GLFW_KEY_A, true)) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		//std::cout << "CameraPosition : (" + std::to_string(cameraPos.x) + " , " + std::to_string(cameraPos.y) + " , " + std::to_string(cameraPos.z) + ")" << std::endl;
 
		glm::vec2 mouseDelta = Application::getMouseDelta(true) * mouseSensitivity;

		yaw += mouseDelta.x;
		pitch -= mouseDelta.y;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		//direction explained : https://uploads.disquscdn.com/images/58fa1f1a3dd8d736a9345b3b168dd55caf0f14d485e9dae7e06b8e185348a42a.png

		cameraFront = glm::normalize(direction);


		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); //cameraPos + cameraFront = cameraTarget


		/*----------------------------------------------------------------------------------------*/
		//projection
		Window* window = Application::getWindow();
		projection = glm::perspective(glm::radians(45.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);

		vertexPipeline->bindAll();
		texture1->bind(1);
		texture2->bind(2);
		shader->use();
		shader->uploadMat4f("view", view, false);
		shader->uploadMat4f("projection", projection, false);

		shader->uploadTexture("texture1", 1, false);
		shader->uploadTexture("texture2", 2, false);

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader->uploadMat4f("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		texture1->unbind();
		vertexPipeline->unbindAll();
		shader->detach();
	}
	void onImguiUpdate(const TimeStep& ts) override {

	}


};