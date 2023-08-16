#pragma once
#include "GLCoreLayer.hpp"
#include "GLCoreGraphicsExtensions.hpp"
#include "GLCore/Extension/Uniforms/Camera.hpp"

using namespace GLCore;

class Layer_CameraClass : public Layer {
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
		glm::vec3(-1.3f,  2.0f, -1.5f),
		glm::vec3(-1.3f,  5.0f, -1.5f),
		glm::vec3(-1.3f,  -2.0f, -1.5f),
		glm::vec3(-1.3f,  -20.0f, -1.5f)
	};

	Uniforms::Camera camera;

public:
	Layer_CameraClass() : Layer("CameraClass") {};

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

		
		Uniforms::CameraSettings cameraSettings(0.2f, 10.0f);
		camera = Uniforms::Camera(cameraSettings);
		camera.setView(
			glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		Window* window = Application::getWindow();
		camera.setProjection(
			glm::perspective(glm::radians(45.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f));

		camera.enable_walkAround_with_keyboard();
		camera.enable_lookAround_with_mouse();
		camera.enable_lookAround_with_rightClick_mouse();
		camera.limit_pitch_to();
	}
	void onDetach() override {

	}
	void onUpdate(const TimeStep& ts) override {
		camera.onUpdate(ts);
		camera.updateView();

		/*----------------------------------------------------------*/
		vertexPipeline->bindAll();
		texture1->bind(1);
		texture2->bind(2);
		shader->use();
		camera.uploadView(shader);
		camera.uploadProjection(shader);

		shader->uploadTexture("texture1", 1, false);
		shader->uploadTexture("texture2", 2, false);
		/*----------------------------------------------------------*/
		/*Model*/
		for (int i = 0; i < cubePositions.size(); i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			camera.setModel(model);
			camera.uploadModel(shader);

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