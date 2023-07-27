#include "glpch.hpp"
#include "VBO.hpp"

namespace GLCore::Primitives {
	void VBO::create() {
		glGenBuffers(1, &VBOID);
		glBindBuffer(GL_ARRAY_BUFFER, VBOID);

		if (vertices == nullptr) {
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), nullptr, _DRAW_TYPE);
		}
		else {
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices->data(), _DRAW_TYPE);
		}
	}

	void VBO::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	}
	void VBO::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	}
	void VBO::destroy() {
		glDeleteBuffers(GL_ARRAY_BUFFER, &VBOID);
	}
}