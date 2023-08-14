#pragma once
#include "GLCoreLayer.hpp"
#include "GLCoreGraphicsExtensions.hpp"

using namespace GLCore;

class Layer_Transformations : public Layer {
private:
	Shaders::Shader* shader = nullptr;
	Primitives::Texture* texture1 = nullptr;
	Primitives::Texture* texture2 = nullptr;

	std::shared_ptr<Primitives::VertexAttributes> vertexAttributes = nullptr;
	std::unique_ptr<Primitives::VertexPipeline> vertexPipeline = nullptr;
private:
	const int POS_SIZE = 3;
	const int TEX_SIZE = 2;
	const int COLOR_SIZE = 3;
	const int VERTEX_SIZE = POS_SIZE + TEX_SIZE + COLOR_SIZE;

	std::vector<float> vertices = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	std::vector<unsigned int> indices = {
		// First square (two triangles)
			   0, 1, 2, // Triangle 1: Bottom left, Bottom right, Top left
			   0, 3, 2, // Triangle 2: Bottom right, Top right, Top left
	};



public:
	Layer_Transformations() : Layer("Layer_Transformations") {};

	void onAttach() override {
		shader = util::AssetPool::getShader("SquareShader");
		
		vertexAttributes = Primitives::VertexAttributes::create();
		vertexAttributes->addVertexAttribute(0, POS_SIZE , GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)0);
		vertexAttributes->addVertexAttribute(1, COLOR_SIZE , GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)(POS_SIZE * sizeof(float)));
		vertexAttributes->addVertexAttribute(2, TEX_SIZE , GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)( (POS_SIZE + COLOR_SIZE) * sizeof(float)));

		vertexPipeline = Primitives::VertexPipeline::create();
		vertexPipeline->setVBO(GL_STATIC_DRAW, vertices.size(), &vertices);
		vertexPipeline->setVAO();
		vertexPipeline->setEBO(&indices);
		vertexPipeline->setVertexAttributes(vertexAttributes);
		vertexPipeline->configure();

		texture1 = util::AssetPool::getTexture("OpenGL-Examples/assets/textures/gears.png");
		texture2 = util::AssetPool::getTexture("OpenGL-Examples/assets/textures/shinGodzilla.jpg");

	}
	void onDetach() override {
		
	}
	void onUpdate(const TimeStep& ts) override {
		// create transformations
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-float(ts) * 10 ), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		Window* window = Application::getWindow();

		projection = glm::perspective(glm::radians(45.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);


		vertexPipeline->bindAll();
		texture1->bind(1);
		texture2->bind(2);
		shader->use();
		shader->uploadMat4f("model", model, false);
		shader->uploadMat4f("view", view, false);
		shader->uploadMat4f("projection", projection, false);

		shader->uploadTexture("texture1", 1, false);
		shader->uploadTexture("texture2", 2, false);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

		texture1->unbind();
		vertexPipeline->unbindAll();
		shader->detach();
	}
	void onImguiUpdate(const TimeStep& ts) override {

	}
	

};