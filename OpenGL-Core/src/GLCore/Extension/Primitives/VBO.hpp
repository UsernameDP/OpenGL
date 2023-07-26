#pragma once
#include "GLCore/Extension/Extension.hpp"
#include "EBO.hpp"

namespace GLCore {
	class VBO {
	private:
		GLuint VBOID;
		size_t size;
		std::vector<float>* vertices;
		/*
		Implementing vertices via. reference will still work
		given that the vertices is not destroyed before
		the vertices data is uploaded to GPU via. 
		glBufferData()
		*/
		GLenum _DRAW_TYPE;
	public:
		VBO() {};
		VBO(GLenum i_DRAW_TYPE,
			size_t i_size, // sizeof(float) is already accounted for
			std::vector<float>* i_vertices = nullptr
		) :
			VBOID(0),
			size(i_size),
			vertices(i_vertices),
			_DRAW_TYPE(i_DRAW_TYPE) {};

		void create();

		void bind();
		void unbind();
		void destroy();

		//void dynamicData(std::vector<float>* i_vertices);
	};
}