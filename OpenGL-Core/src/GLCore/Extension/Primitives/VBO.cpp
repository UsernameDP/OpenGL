#include "pch.hpp"
#include "VBO.hpp"

namespace GLCore::Primitives {
	void VBO::create() {
		glGenBuffers(1, &VBOID);
		glBindBuffer(GL_ARRAY_BUFFER, VBOID);

		if (vertices == nullptr) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, _DRAW_TYPE);
		}
		else {
			std::cout << sizeof(vertices->data()) << std::endl;
			glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), _DRAW_TYPE);
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