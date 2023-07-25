#pragma once
#include <glad/glad.h>

namespace GLCore {
	class EBO {
	private:
		unsigned int EBOID;
	public:
		EBO(std::vector<int>& indices);

		void bind();
		void unbind();
		void destroy();
	};
}