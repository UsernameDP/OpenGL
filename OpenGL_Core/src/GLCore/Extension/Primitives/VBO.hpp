#pragma once
#include "GLBufferObject.hpp"

namespace GLCore::Extension::Primitives {
	class VBO : public GLBufferObject {
	private:
		std::vector<float>* vertices;
		/*
		* Using vectors will still work b/c
		array->data() returns the raw float[] of vertices, 
		it may seem off b/c sizeof(vertices) is not the same as sizeof(float[]) but it truly does return the raw float[]
		
		vertices->size() * sizeof(float) is the same as sizeof(float[]) 
		*/
		GLenum _DRAW_TYPE;
	public:
		VBO(const GLenum& _DRAW_TYPE,
			std::vector<float>* vertices = nullptr
		);

		void create() override;
		void destroy() override;

		//void dynamicData(std::vector<float>* i_vertices);
	};
}