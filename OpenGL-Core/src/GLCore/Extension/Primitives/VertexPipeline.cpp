#include "glpch.hpp"
#include "VertexPipeline.hpp"

namespace GLCore {
	void VertexPipeline::configure() {

	}
	void VertexPipeline::bindAll() {
		vao->bind();
		vbo->bind();
		if (ebo != nullptr) 
			ebo->bind();
	}

}