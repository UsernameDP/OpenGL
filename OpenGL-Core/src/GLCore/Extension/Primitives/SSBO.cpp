#include "pch.hpp"
#include "SSBO.hpp"

namespace GLCore::Primitives {
	SSBO::~SSBO() {
		destroy();
	}

	void SSBO::createBatchData() {
		if (batchedData != nullptr || BATCH_OFFSET_WITH_DATATYPE > 0) {
			THROW_RUNTIME_ERROR("Make sure to run destroyBatchData() after createBatchData() for SSBO");
		}

		BasicBind();
		batchedData = glMapBuffer(SSBOID, GL_WRITE_ONLY);
	}
	void SSBO::destroyBatchData() {
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		BasicUnbind();

		BATCH_OFFSET_WITH_DATATYPE = 0;
		batchedData = nullptr;
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