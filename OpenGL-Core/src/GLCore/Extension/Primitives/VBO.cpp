#include "glpch.hpp"
#include "VBO.hpp"

namespace GLCore {
	VBO::VBO(GLenum _DRAW_TYPE, size_t memory_allocated_gpu, std::vector<float>* vertices):
		VBOID(0),
		max_vector_size(max_vector_size),
		_DRAW_TYPE(_DRAW_TYPE),
		vertices(vertices) {
		glGenBuffers(1, &VBOID);
		glBindBuffer(GL_ARRAY_BUFFER, VBOID);

		if (vertices == nullptr) {
			glBufferData(GL_ARRAY_BUFFER, max_vector_size * sizeof(float), nullptr, _DRAW_TYPE);
		}
		else {
			glBufferData(GL_ARRAY_BUFFER, max_vector_size * sizeof(float), vertices->data(), _DRAW_TYPE);
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