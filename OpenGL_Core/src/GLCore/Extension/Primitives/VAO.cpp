#include "pch.hpp"
#include "VAO.hpp"

namespace GLCore::Extension::Primitives {
	void VAO::create() {
		glGenVertexArrays(1, & ID);
		glBindVertexArray(ID);
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