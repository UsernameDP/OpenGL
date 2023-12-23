#include "pch.hpp"
#include "VBO.hpp"

namespace GLCore::Extension::Primitives
{
	VBO::VBO(const GLenum &DRAW_TYPE, std::vector<float> *vertices) : GLBufferObject(GL_ARRAY_BUFFER), DRAW_TYPE(DRAW_TYPE), vertices(vertices) {}

	void VBO::create()
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), this->DRAW_TYPE);
	}

	void VBO::destroy()
	{
		glDeleteBuffers(GL_ARRAY_BUFFER, &ID);
	}
}