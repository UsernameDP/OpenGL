#include "pch.hpp"
#include "SSBO.hpp"

namespace GLCore::Primitives {
	SSBO::~SSBO() {
		destroy();
	}
	SSBO::SSBO(const GLenum& _DRAW_TYPE, 
		const size_t& size,
		std::vector<float>* data) {
		this->size = static_cast<unsigned int>(size);
		this->_DRAW_TYPE = _DRAW_TYPE;
		this->data = data;
	}

	void SSBO::create() {
		glGenBuffers(1, &SSBOID);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID);

		if (data == nullptr) {
			glBufferData(GL_SHADER_STORAGE_BUFFER, size * sizeof(float), nullptr, _DRAW_TYPE);
		}
		else {
			glBufferData(GL_SHADER_STORAGE_BUFFER, data->size() * sizeof(float), data->data(), _DRAW_TYPE);
		}
	}

	void SSBO::bind(const unsigned int& bindIndx) {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindIndx, SSBOID);
	}
	void SSBO::unbind() {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBOID);
	}
	void SSBO::destroy() {
		glDeleteBuffers(1, &SSBOID);
	}
}