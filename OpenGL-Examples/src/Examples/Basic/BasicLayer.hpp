#pragma once
#include "GLCoreLayer.hpp"

using namespace GLCore;

class BasicLayer : public Layer {
private:
	Shaders::Shader* shader = nullptr;
	std::shared_ptr<Primitives::VertexAttributes> vertexAttributes = nullptr;
	std::unique_ptr<Primitives::VertexPipeline> vertexPipeline = nullptr;
private:
	const int POS_SIZE = 2;
	const int COLOR_SIZE = 3;
	const int VERTEX_SIZE = POS_SIZE + COLOR_SIZE;

	std::vector<float> vertices = {
		// First square
			 -0.5f, -0.5f, // Position: Bottom left (x, y)
			  1.0f, 0.0f, 0.0f, // Color: Red (r, g, b)

			  0.5f, -0.5f, // Position: Bottom right (x, y)
			  0.0f, 1.0f, 0.0f, // Color: Green (r, g, b)

			 -0.5f,  0.5f, // Position: Top left (x, y)
			  0.0f, 0.0f, 1.0f, // Color: Blue (r, g, b)

			  0.5f,  0.5f, // Position: Top right (x, y)
			  1.0f, 1.0f, 1.0f  // Color: White (r, g, b)
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
		vertexAttributes->addVertexAttribute(1, COLOR_SIZE , GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)(POS_SIZE * sizeof(float)));

		vertexPipeline = Primitives::VertexPipeline::create();
		vertexPipeline->setVBO(GL_STATIC_DRAW, vertices.size(), &vertices);
		vertexPipeline->setVAO();
		vertexPipeline->setEBO(&indices);
		vertexPipeline->setVertexAttributes(vertexAttributes);
		vertexPipeline->configure();
	}
	void onDetach() override {

	}
	void onUpdate(const TimeStep& ts) {
		vertexPipeline->bindAll();
		shader->use();

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

		vertexPipeline->unbindAll();
		shader->detach();
	}
	void onImguiUpdate(const TimeStep& ts) {

	}
	

};