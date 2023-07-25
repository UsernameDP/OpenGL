#pragma once
#include <glad/glad.h>

namespace GLCore {
	class VBO {
	private:
		GLuint VBOID;
		size_t max_vector_size; 
		std::vector<float>* vertices;
		/*
		Implementing vertices via. reference will still work
		given that the vertices is not destroyed before
		the vertices data is uploaded to GPU via. 
		glBufferData()
		*/
		GLenum _DRAW_TYPE;
	public:
		VBO(GLenum _DRAW_TYPE,
			size_t memory_allocated_gpu, // sizeof(float) is already accounted for
			std::vector<float>* vertices = nullptr
			);

		void bind();
		void unbind();
		void destroy();
	};
}