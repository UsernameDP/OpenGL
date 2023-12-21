#pragma once
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VertexAttributes.hpp"

#include <iostream>

namespace GLCore::Extension::Primitives
{

	class VertexPipeline
	{
	public:
		std::shared_ptr<VAO> vao; // create in heap
		std::shared_ptr<VBO> vbo; // create in heap
		std::shared_ptr<EBO> ebo; // create in heap
		std::shared_ptr<VertexAttributes> vertexAttributes;

	public:
		VertexPipeline(){};

		void configure(); // configures the VAO
		void bindAll();
		void unbindAll();

		inline void setVAO(std::shared_ptr<VAO> vao) { this->vao = vao; }
		inline void setVBO(std::shared_ptr<VBO> vbo) { this->vbo = vbo; }
		inline void setEBO(std::shared_ptr<EBO> ebo) { this->ebo = ebo; }

		inline void setVAO()
		{
			vao = std::make_shared<VAO>();
		};
		inline void setVBO(const GLenum DRAW_TYPE, std::vector<float> *vertices)
		{
			vbo = std::make_shared<VBO>(DRAW_TYPE, vertices);
		}
		inline void setEBO(std::vector<unsigned int> *indices)
		{
			ebo = std::make_shared<EBO>(indices);
		}

		inline void setVertexAttributes(std::shared_ptr<VertexAttributes> vertexAttributes)
		{
			this->vertexAttributes = vertexAttributes;
		}

	public:
		static inline std::unique_ptr<VertexPipeline> create()
		{
			return std::make_unique<VertexPipeline>();
		}
	};
}