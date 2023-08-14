#pragma once
#include "../Extension.hpp"
#include "EBO.hpp"

namespace GLCore::Primitives {
	class VBO {
	private:
		GLuint VBOID;
		unsigned int size;
		std::vector<float>* vertices;
		/*
		* Using vectors will still work b/c
		array->data() returns the raw float[] of vertices, 
		it may seem off b/c sizeof(vertices) is not the same as sizeof(float[]) but it truly does return the raw float[]
		
		vertices->size() * sizeof(float) is the same as sizeof(float[]) 
		*/
		GLenum _DRAW_TYPE;
	public:
		VBO() {};
		VBO(const GLenum& _DRAW_TYPE,
			const unsigned int& size, // sizeof(float) is already accounted for
			std::vector<float>* vertices = nullptr
		);

		void create();

		void bind();
		void unbind();
		void destroy();

		//void dynamicData(std::vector<float>* i_vertices);
	};
}