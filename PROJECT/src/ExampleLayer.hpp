#pragma once
#include "GLCore/Core/Core.hpp"
#include "GLCore/Extension/Extension.hpp"

using namespace GLCore;
using namespace GLCore::Extension;
using namespace GLCore::Extension::Primitives;
using namespace GLCore::Extension::Shaders;

class ExampleLayer : public Layer {
private:
	Shader* shader;
	std::shared_ptr<VertexAttributes> vertexAttributes;
	std::unique_ptr<VertexPipeline> pipeline;

	std::vector<float> vertices = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
	};

	// Indices for a rectangle
	std::vector<unsigned int> indices = {
		0, 1, 3, 2
	};

public:
	ExampleLayer() = default;
	~ExampleLayer() override {

	}

	void onAttach() override {
		shader = &AssetPool::getShader("Square");

		pipeline = VertexPipeline::create();

		pipeline->setVAO();
		pipeline->setEBO(&indices);
		pipeline->setVBO(GL_STATIC_DRAW, &vertices);

		vertexAttributes = std::make_shared<VertexAttributes>();
		vertexAttributes->addVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		pipeline->setVertexAttributes(vertexAttributes);

		pipeline->configure();
	}
	void onDetach() override {
		
	}
	void onUpdate(const GLCore::TimeStep& ts) override {

		pipeline->bindAll();
		shader->use();

		//glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

		pipeline->unbindAll();
		shader->detach();

	}
	void onImguiUpdate(const GLCore::TimeStep& ts) override {

		ImGui::ShowDemoWindow();

		if (GLCore::Application::get().getKeyPressed(GLFW_KEY_F)) {
			std::cout << "Key F is being pressed" << std::endl;
		}
	}

};