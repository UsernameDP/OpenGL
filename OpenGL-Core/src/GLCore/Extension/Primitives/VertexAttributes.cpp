#include "pch.hpp"
#include "VertexAttributes.hpp"

namespace GLCore::Primitives {
	VertexAttributes::~VertexAttributes() {
		for (VertexAttribute* attribute : vertexAttributes_vector) {
			delete attribute;
		}
	}

	void VertexAttributes::setAttributes() {
		for (VertexAttribute* attribute : vertexAttributes_vector) {
			glVertexAttribPointer(
				attribute->index,
				attribute->size,
				attribute->type,
				attribute->normalized,
				attribute->stride,
				attribute->pointer);
			glEnableVertexAttribArray(attribute->index);
		}
		disableAttributes();
	}
	void VertexAttributes::enableAttributes() {
		for (VertexAttribute* attribute : vertexAttributes_vector) {
			glEnableVertexAttribArray(attribute->index);
		}
	}
	void VertexAttributes::disableAttributes() {
		for (VertexAttribute* attribute : vertexAttributes_vector) {
			glDisableVertexAttribArray(attribute->index);
		}
	}
}