#pragma once
#include "GLCore/Extension/Extension.hpp"

namespace GLCore {
	class VAO {
	private:
		GLuint VAOID;
	public:
		VAO() {};

		void create();
		void bind();
		void unbind();
		void destroy();
	};
}