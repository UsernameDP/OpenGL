#pragma once
#include "Shader.hpp"

namespace GLCore::Shaders {
	class ComputeShader : public Shader {
	public:
		ComputeShader(const std::string& name, const std::string& computePath);
	public:
		static inline void dispatchComputeShader(const glm::ivec3& dispatchDimensions) {
			glDispatchCompute(dispatchDimensions.x, dispatchDimensions.y, dispatchDimensions.z);
		}


		static inline void runWithMemoryBarrier(const GLbitfield& barrierMethod = GL_ALL_BARRIER_BITS) {
			glMemoryBarrier(barrierMethod);
		}
	};
}