#include "glpch.hpp"
#include "VertexPipeline.hpp"

namespace GLCore::Primitives {
	void VertexPipeline::configure() {
		vbo->create();
		vao->create();
		vertexAttributes->setAttributes();
		if (ebo != nullptr) ebo->create();

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