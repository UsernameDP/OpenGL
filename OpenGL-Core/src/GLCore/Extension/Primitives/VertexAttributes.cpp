#include "glpch.hpp"
#include "VertexAttributes.hpp"

namespace GLCore {
	VertexAttributes::~VertexAttributes() {
		for (VertexAttribute* attribute : vertexAttributes) {
			delete attribute;
		}
	}
}