#include "glpch.hpp"
#include "VertexPipeline.hpp"

namespace GLCore::Primitives {
	void VertexPipeline::configure() {
		vao->create();
		vbo->create();
		if (ebo != nullptr) ebo->create();
		vertexAttributes->setAttributes();

		unbindAll();
	}
	void VertexPipeline::bindAll() {
		vbo->bind();
		vao->bind();
		vertexAttributes->enableAttributes();
		if(ebo != nullptr) ebo->bind();
	}
	void VertexPipeline::unbindAll() {
		if (ebo != nullptr) ebo->unbind();
		vertexAttributes->disableAttributes();
		vao->unbind();
		vbo->unbind();
	}
}