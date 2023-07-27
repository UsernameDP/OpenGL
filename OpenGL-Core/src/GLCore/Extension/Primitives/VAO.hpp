#pragma once
#include "../Extension.hpp"

namespace GLCore::Primitives {
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