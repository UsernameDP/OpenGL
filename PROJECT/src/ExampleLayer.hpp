#pragma once
#include "GLCore/Core/Core.hpp"
#include "GLCore/Extension/Extension.hpp"

using namespace GLCore;

class ExampleLayer : public Layer
{
private:
private:
	Extension::Shaders::Shader* shader;
	std::unique_ptr<Extension::Primitives::VBO> vbo;
	std::unique_ptr<Extension::Primitives::VAO> vao;
	std::unique_ptr<Extension::Primitives::VertexAttributes> vertexAttributes;

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Vertex 0 (position + color)
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Vertex 1 (position + color)
		0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f	  // Vertex 2 (position + color)
	};

	Extension::Shaders::ComputeShader* computeShader;
	std::unique_ptr<Extension::Primitives::SSBO> ssbo;

	struct Point {
		glm::vec3 pos;
		glm::vec3 color;
	};

	std::vector<Point> points = {
		{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
		// ... add more points as needed
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
		//VertexPipelineShader Testing
		shader = &Extension::AssetPool::getShader("Triangle");

		vertexAttributes = std::make_unique<Extension::Primitives::VertexAttributes>();
		vertexAttributes->addVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);					// Position
		vertexAttributes->addVertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // Color

		vao = std::make_unique<Extension::Primitives::VAO>();
		vbo = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, &vertices);
		vertexAttributes->setAttributes();

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

		ssbo->bind();
		void* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		if (p) {
			memcpy(points.data(), p, points.size() * sizeof(Point));
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

			for (const Point& point : points) {
				std::cout << "Position: (" << point.pos.x << ", " << point.pos.y << ", " << point.pos.z << "), "
					<< "Color: (" << point.color.r << ", " << point.color.g << ", " << point.color.b << ")" << std::endl;
			}
		}		


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