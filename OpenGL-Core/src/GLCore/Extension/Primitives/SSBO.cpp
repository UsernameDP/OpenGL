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
		this->size_with_dataType = size * sizeof(float);
		this->_DRAW_TYPE = _DRAW_TYPE;
		this->data = data;
	}

	void SSBO::create() {
		glGenBuffers(1, &SSBOID);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID);
		if (data == nullptr) {
			glBufferData(GL_SHADER_STORAGE_BUFFER, this->size_with_dataType, nullptr, _DRAW_TYPE);
		}
		else {
			glBufferData(GL_SHADER_STORAGE_BUFFER, this->size_with_dataType, data->data(), _DRAW_TYPE);
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

	void SSBO::readDataTo(std::vector<float>* destination) {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOID); //determines which ssbo to read(map from)
		
		//Map the buffer and copy data
		void* mappedBuffer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		if (mappedBuffer) {
			if (destination->size() != this->size) destination->resize(this->size);

			memcpy(destination->data(), mappedBuffer, this->size_with_dataType);
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
}