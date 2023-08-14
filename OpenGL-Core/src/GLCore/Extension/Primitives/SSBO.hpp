#pragma once
#include "../Extension.hpp"

namespace GLCore::Primitives {

	class SSBO {
	private:
		GLuint SSBOID;
		unsigned int size;
		std::vector<float>* data;
		GLenum _DRAW_TYPE;
		
	public:
		SSBO() = default;
		SSBO(const GLenum& _DRAW_TYPE, 
			const size_t& size,
			std::vector<float>* data = nullptr
		);
		~SSBO(); //for smart_ptr instantiations

		void create();

		void bind(const unsigned int& bindIndx = 0);
		void unbind();
		void destroy();
	};
}