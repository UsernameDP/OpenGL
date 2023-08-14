#include "pch.hpp"
#include "ComputeShader.hpp"

namespace GLCore::Shaders {

	ComputeShader::ComputeShader(const std::string& name, const std::string& computePath,
		const glm::ivec3& dispatchDimensions, const GLbitfield& memorySyncMethod)
		: Shader(name) {

		addPrimitiveShader(GL_COMPUTE_SHADER, computePath);
		compile();

		this->dispatchDimensions = dispatchDimensions;
		this->memorySyncMethod = memorySyncMethod;
	}

	void ComputeShader::use() {
		Shader::use();
		std::cout << dispatchDimensions.x;

		glDispatchCompute(dispatchDimensions.x, dispatchDimensions.y, dispatchDimensions.z);
		glMemoryBarrier(memorySyncMethod);
	}
}