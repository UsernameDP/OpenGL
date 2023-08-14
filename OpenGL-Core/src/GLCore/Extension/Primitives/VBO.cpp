#include "pch.hpp"
#include "VBO.hpp"

namespace GLCore::Primitives {
	VBO::VBO(const GLenum& DRAW_TYPE,
		const unsigned int& size, 
		std::vector<float>* vertices) {
		this->_DRAW_TYPE = DRAW_TYPE;
		this->size = size;
		this->vertices = vertices;
	}

	void VBO::create() {
		glGenBuffers(1, &VBOID);
		glBindBuffer(GL_ARRAY_BUFFER, VBOID);

		if (vertices == nullptr) {
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), nullptr, _DRAW_TYPE);
		}
		else {
			glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), _DRAW_TYPE);
		}
	}

	void VBO::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	}
	void VBO::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VBO::destroy() {
		glDeleteBuffers(GL_ARRAY_BUFFER, &VBOID);
	}
}