#pragma once
#include "Shader.hpp"

namespace GLCore::Shaders {
	class ComputeShader : public Shader {
	private:
		glm::ivec3 dispatchDimensions;
		GLbitfield memorySyncMethod;

	public:
		ComputeShader(const std::string& name, const std::string& computePath, 
			const glm::ivec3& dispatchDimensions, 
			const GLbitfield& memorySyncMethod = GL_ALL_BARRIER_BITS);

		void use() override;
	};
}