#pragma once
#include "../Extension.hpp"

namespace GLCore::Primitives {
	class EBO {
	private:
		unsigned int EBOID;
		std::vector<int>* indices;
	public:
		EBO(std::vector<int>* i_indices) : indices(i_indices) {};

		void create();

		void bind();
		void unbind();
		void destroy();
	public:
		//static void generateIndices(unsigned int n_polygon, unsigned int vertices,
		//	std::vector<int>& indiceArr); 
		/*If i ever have a generate indices, it will be like this, indiceArr is 
		editing inside of the function s.t i don't have to copy the entire
		indice arr when i return or have to create anything in heap via. 
		new operator*/

		//static void generateIndices_LINE(unsigned int n_polygon, unsigned int vertices, std::vector<int>& indiceArr);
	};
}