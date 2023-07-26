#pragma once
#include "GLCore/Extension/Extension.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

namespace GLCore {
	struct VertexAttribute {
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer;
	};

	class VertexPipeline {
	private:
		VAO* vao; //create in heap
		VBO* vbo; //create in heap
		EBO* ebo; //create in heap

		std::vector<unsigned int*> vertexAttributeIndexes;
		std::vector<VertexAttribute*> vertexAttributes; 
	public:
		VertexPipeline() :
			vao(nullptr),
			vbo(nullptr),
			ebo(nullptr) {};

		void configure(); //configures the VAO
		void bindAll();
		void unbindAll();

		inline void setVAO(VAO* vao) { this->vao = vao; }
		inline void setVBO(VBO* vbo) { this->vbo = vbo; }
		inline void setEBO(EBO* ebo) { this->ebo = ebo; }

		//createVBO(params...), createVAO(params...) instead?
	};
}