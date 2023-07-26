#include "glpch.hpp"
#include "EBO.hpp"
#include <cmath>

namespace GLCore {	
	void EBO::create() {
		glGenBuffers(1, &EBOID);
		glBindBuffer(GL_ARRAY_BUFFER, EBOID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(float), indices->data(), GL_STATIC_DRAW);
	}
	void EBO::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, EBOID);
	}
	void EBO::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, EBOID);
	}
	void EBO::destroy() {
		glDeleteBuffers(GL_ARRAY_BUFFER, &EBOID);
	}
}