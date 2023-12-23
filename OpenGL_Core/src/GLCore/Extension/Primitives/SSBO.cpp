#include "pch.hpp"
#include "SSBO.hpp"

namespace GLCore::Extension::Primitives {
	void SSBO::bindAt(const GLuint& loc)
	{
		bind();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, loc, ID);
	}
}