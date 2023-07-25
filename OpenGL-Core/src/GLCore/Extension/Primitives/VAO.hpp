#pragma once
#include <vector>
#include <glad/glad.h>

namespace GLCore {
	class VAO {
	private:
		GLuint VAOID;
		std::vector<unsigned int> vertexAttributes;
	public:
		VAO();

		void addVertexAttribute();
		void bind();
		void unbind();
		void destroy();
	};
}