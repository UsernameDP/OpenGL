#include "pch.hpp"
#include "VAO.hpp"

namespace GLCore::Extension::Primitives {
	VAO::VAO() : GLBindableInterface() {
		glGenVertexArrays(1, &ID);
		bind();
	}
	VAO::~VAO() {
		unbind();
		destroy();
	}

	void VAO::bind() {
		glBindVertexArray(ID);
	}
	void VAO::unbind() {
		glBindVertexArray(0);
	}
	void Primitives::VAO::destroy()
	{
		glDeleteVertexArrays(1, &ID);
	}
}