#pragma once
#include "GLCore/Extension/Extension.hpp"

namespace GLCore {
	struct VertexAttribute {
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer;
	};

	class VertexAttributes {
	private:
		std::vector<VertexAttribute*> vertexAttributes;
	public:
		VertexAttributes() {};
		~VertexAttributes();

		inline void addVertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
			vertexAttributes.push_back(new VertexAttribute{ index, size, type, normalized, stride, pointer });
		}

		std::vector<VertexAttribute*>::iterator begin() { return vertexAttributes.begin(); }
		std::vector<VertexAttribute*>::iterator end() { return vertexAttributes.end(); }

	public:
		static inline std::shared_ptr<VertexAttributes> create() { 
			return std::make_shared<VertexAttributes>(); 
		}
	};
}