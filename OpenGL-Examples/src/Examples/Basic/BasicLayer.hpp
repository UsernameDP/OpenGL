#pragma once
#include "GLCoreLayer.hpp"
#include "GLCoreExtension.hpp"

using namespace GLCore;

class BasicLayer : public Layer {
private:
	Shaders::Shader* shader = nullptr;
	Primitives::Texture* testTexture = nullptr;
	std::shared_ptr<Primitives::VertexAttributes> vertexAttributes = nullptr;
	std::unique_ptr<Primitives::VertexPipeline> vertexPipeline = nullptr;
private:
	const int POS_SIZE = 2;
	const int TEX_SIZE = 2;
	const int COLOR_SIZE = 3;
	const int VERTEX_SIZE = POS_SIZE + TEX_SIZE;

	std::vector<float> vertices = {
		// First square
			 -0.5f, -0.5f, // Position: Bottom left (x, y)
			  0.0f, 0.0f,   // Tex Coords Bottom Left of Texture

			  0.5f, -0.5f, // Position: Bottom right (x, y)
			  1.0f, 0.0f,

			 -0.5f,  0.5f, // Position: Top left (x, y)
			  0.0f, 1.0f,

			  0.5f,  0.5f, // Position: Top right (x, y)
			  1.0f, 1.0f
	};

	std::vector<unsigned int> indices = {
		// First square (two triangles)
			   0, 1, 2, // Triangle 1: Bottom left, Bottom right, Top left
			   1, 3, 2, // Triangle 2: Bottom right, Top right, Top left
	};



public:
	BasicLayer() : Layer("BasicLayer") {};

	void onAttach() override {
		shader = util::AssetPool::getShader("SquareShader");
		
		vertexAttributes = Primitives::VertexAttributes::create();
		vertexAttributes->addVertexAttribute(0, POS_SIZE , GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)0);
		vertexAttributes->addVertexAttribute(1, TEX_SIZE , GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)(POS_SIZE * sizeof(float)));

		vertexPipeline = Primitives::VertexPipeline::create();
		vertexPipeline->setVBO(GL_STATIC_DRAW, vertices.size(), &vertices);
		vertexPipeline->setVAO();
		vertexPipeline->setEBO(&indices);
		vertexPipeline->setVertexAttributes(vertexAttributes);
		vertexPipeline->configure();

		testTexture = util::AssetPool::getTexture("OpenGL-Examples/assets/textures/gears.png");
	}
	void onDetach() override {
		
	}
	void onUpdate(const TimeStep& ts) override {

		vertexPipeline->bindAll();
		testTexture->bind(1);
		shader->use();
		shader->uploadTexture("u_Texture", 1);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

		testTexture->unbind();
		vertexPipeline->unbindAll();
		shader->detach();
	}
	void onImguiUpdate(const TimeStep& ts) override {

	}
	

};