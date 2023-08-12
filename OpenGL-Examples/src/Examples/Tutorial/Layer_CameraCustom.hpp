#pragma once
#include "GLCoreLayer.hpp"
#include "GLCoreExtension.hpp"
#include <cmath>

using namespace GLCore;

class Layer_CameraCustom : public Layer {
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

	//Camera (view)
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	float yaw = -90.0f; // theta X 
	float pitch = 0.0f; //theta Y

public:
	Layer_CameraCustom() : Layer("CameraCustom") {};

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
		glm::mat4 view = glm::mat4(1.0f); //unit matrix
		glm::mat4 projection = glm::mat4(1.0f);

		//Factors
		const float sensitivity = 0.1f;
		float cameraSpeed = 2.5f * ts.getDeltaSeconds();

		/*View*/
		//Move around
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
		//Look around
		glm::vec2 mouseDelta = Application::getMouseDelta(true) * sensitivity;
		yaw += mouseDelta.x;
		pitch -= mouseDelta.y; //lastPosY - currentPosY, when go up, currentPosY > lastPosY, hence 0 > lastPosY - currentPosY
		
		glm::vec3 direction;
		direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		direction.y = sin(glm::radians(pitch));
		direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

		cameraFront = glm::normalize(direction);

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); //cameraPos + cameraFront = cameraTarget

		/*Projection*/
		Window* window = Application::getWindow();
		projection = glm::perspective(glm::radians(45.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);

		/*----------------------------------------------------------*/
		vertexPipeline->bindAll();
		texture1->bind(1);
		texture2->bind(2);
		shader->use();
		shader->uploadMat4f("view", view, false);
		shader->uploadMat4f("projection", projection, false);

		shader->uploadTexture("texture1", 1, false);
		shader->uploadTexture("texture2", 2, false);
		/*----------------------------------------------------------*/
		/*Model*/
		for (int i = 0; i < cubePositions.size(); i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			shader->uploadMat4f("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		/*----------------------------------------------------------*/
		texture1->unbind();
		vertexPipeline->unbindAll();
		shader->detach();
	}
	void onImguiUpdate(const TimeStep& ts) override {

	}


};