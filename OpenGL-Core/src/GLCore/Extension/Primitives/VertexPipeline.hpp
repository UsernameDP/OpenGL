#pragma once
#include "../Extension.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VertexAttributes.hpp"

namespace GLCore::Primitives {

	class VertexPipeline {
	public:
		std::unique_ptr<VAO> vao = nullptr; //create in heap
		std::unique_ptr<VBO> vbo = nullptr; //create in heap
		std::unique_ptr<EBO> ebo = nullptr; //create in heap
		std::shared_ptr<VertexAttributes> vertexAttributes = nullptr;
	public:
		VertexPipeline() {};

		void configure(); //configures the VAO
		void bindAll();
		void unbindAll();

		inline void setVAO(std::unique_ptr<VAO> vao) { this->vao = std::move(vao); }
		inline void setVBO(std::unique_ptr<VBO> vbo) { this->vbo = std::move(vbo); }
		inline void setEBO(std::unique_ptr<EBO> ebo) { this->ebo = std::move(ebo); }

		inline void setVAO() { 
			vao = std::make_unique<VAO>(); 
		};
		inline void setVBO(GLenum i_DRAW_TYPE, size_t i_size, std::vector<float>* i_vertices = nullptr) {
			vbo = std::make_unique<VBO>(i_DRAW_TYPE, i_size, i_vertices);
		}
		inline void setEBO(std::vector<unsigned int>* i_indices) {
			ebo = std::make_unique<EBO>(i_indices);
		}

		inline void setVertexAttributes(std::shared_ptr<VertexAttributes> vertexAttributes){
			this->vertexAttributes = vertexAttributes;
		}

	public:
		static inline std::unique_ptr<VertexPipeline> create() {
			return std::make_unique<VertexPipeline>();
		}
	};
}