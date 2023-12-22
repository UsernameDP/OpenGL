#include "pch.hpp"
#include "SSBO.hpp"

namespace GLCore::Extension::Primitives {
	SSBO::SSBO(const GLenum& DRAW_TYPE, const size_t SIZE, const size_t& SIZE_WITH_DATATYPE) : GLBufferObject(GL_SHADER_STORAGE_BUFFER) {
		this->DRAW_TYPE = DRAW_TYPE;
		this->SIZE = SIZE;
		this->SIZE_WITH_DATATYPE = static_cast<unsigned long int>(SIZE_WITH_DATATYPE);

		glGenBuffers(1, &ID);
		bind();

		glBufferData(GL_SHADER_STORAGE_BUFFER, this->SIZE_WITH_DATATYPE, nullptr, this->DRAW_TYPE);
		unbind();
	}


	void SSBO::resetOffset() {
		this->MULTIPLE_BUFFER_OFFSET = 0;
	}

	void SSBO::bindAt(const GLuint& loc)
	{
		bind();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, loc, ID);
	}

	void SSBO::detach() {
		unbind();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ID);
	}

	void SSBO::destroy() {
		glDeleteBuffers(1, &ID);
	}
}