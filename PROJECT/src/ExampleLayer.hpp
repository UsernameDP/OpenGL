#pragma once
#include "GLCore/Core/Core.hpp"
#include "GLCore/Extension/Extension.hpp"

using namespace GLCore;

class ExampleLayer : public Layer
{
private:
private:
	Extension::Shaders::Shader *shader = nullptr;
	std::unique_ptr<Extension::Primitives::VBO> vbo;
	std::unique_ptr<Extension::Primitives::VAO> vao;
	std::unique_ptr<Extension::Primitives::VertexAttributes> vertexAttributes;

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 0 (position + color)
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Vertex 1 (position + color)
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f	  // Vertex 2 (position + color)
	};

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

		vertexAttributes = std::make_unique<Extension::Primitives::VertexAttributes>();
		vertexAttributes->addVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);					// Position
		vertexAttributes->addVertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // Color

		vao = std::make_unique<Extension::Primitives::VAO>();
		vbo = std::make_unique<Extension::Primitives::VBO>(GL_STATIC_DRAW, &vertices);
		vertexAttributes->setAttributes();

		
	}
	virtual void onDetach() override
	{
	}
	virtual void onUpdate(const GLCore::TimeStep &ts) override
	{
		shader->use();
		vao->bind();
		vertexAttributes->enableAttributes();
		shader->uploadFloat("time", ts.getSeconds());

		glDrawArrays(GL_TRIANGLES, 0, 3);

		vertexAttributes->disableAttributes();
		vao->unbind();
		shader->detach();
	}
	virtual void onImguiUpdate(const GLCore::TimeStep &ts) override
	{
		ImGui::ShowDemoWindow();
	}

private:
};