#include "pch.hpp"
#include "SSBO.hpp"

namespace GLCore::Primitives {
	SSBO::SSBO(const GLenum& _DRAW_TYPE, const size_t SIZE, const size_t& SIZE_WITH_DATATYPE) {
		this->_DRAW_TYPE = _DRAW_TYPE;
		this->SIZE = SIZE;
		this->SIZE_WITH_DATATYPE = static_cast<unsigned long int>(SIZE_WITH_DATATYPE);

		glGenBuffers(1, &SSBOID);
		BasicBind();

		glBufferData(GL_SHADER_STORAGE_BUFFER, this->SIZE_WITH_DATATYPE, nullptr, this->_DRAW_TYPE);
		BasicUnbind();
	}
	SSBO::~SSBO() {
		destroy();
	}


	void SSBO::resetOffset() {
		this->MULTIPLE_BUFFER_OFFSET = 0;
	}


	void SSBO::BasicBind() {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID);
	}
	void SSBO::bind(const unsigned int& bindIndx) {
		BasicBind();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindIndx, SSBOID);
	}

	void SSBO::BasicUnbind() {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	void SSBO::unbind() {
		BasicBind();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBOID);
	}

	void SSBO::destroy() {
		glDeleteBuffers(1, &SSBOID);
	}
}