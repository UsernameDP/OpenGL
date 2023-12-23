#pragma once
#include "GLCore/Core/Core.hpp"
#include "GLCore/Extension/Extension.hpp"

using namespace GLCore;

class ExampleLayer : public Layer
{
private:
private:
	Extension::Shaders::Shader *shader = nullptr;
	std::shared_ptr<Extension::Primitives::VertexAttributes> vertexAttributes;
	std::unique_ptr<Extension::Primitives::VertexPipeline> pipeline;

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 0 (position + color)
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Vertex 1 (position + color)
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f	  // Vertex 2 (position + color)
	};

	std::unique_ptr<Extension::Primitives::VBO> vbo;
	std::unique_ptr<Extension::Primitives::VAO> vao;

public:
	ExampleLayer() : Layer("ExampleLayer")
	{
	}
	virtual ~ExampleLayer()
	{
	}

	virtual void onAttach() override
	{
		shader = &Extension::AssetPool::getShader("Square");

		vertexAttributes = std::make_shared<Extension::Primitives::VertexAttributes>();
		vertexAttributes->addVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);					// Position
		vertexAttributes->addVertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // Color

		pipeline = Extension::Primitives::VertexPipeline::create();
		pipeline->setVAO();
		pipeline->setVBO(GL_STATIC_DRAW, &vertices);
		pipeline->setVertexAttributes(vertexAttributes);
		pipeline->configure();

		
	}
	virtual void onDetach() override
	{
	}
	virtual void onUpdate(const GLCore::TimeStep &ts) override
	{
		pipeline->bindAll();
		shader->use();
		shader->uploadFloat("time", ts.getSeconds());

		glDrawArrays(GL_TRIANGLES, 0, 3);

		pipeline->unbindAll();
		shader->detach();
	}
	virtual void onImguiUpdate(const GLCore::TimeStep &ts) override
	{
		ImGui::ShowDemoWindow();
	}

private:
};