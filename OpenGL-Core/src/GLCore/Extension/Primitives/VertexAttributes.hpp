#pragma once
#include "../Extension.hpp"

namespace GLCore::Primitives {
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
		std::vector<VertexAttribute*> vertexAttributes_vector;
	public:
		VertexAttributes();
		~VertexAttributes();

		inline void addVertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
			vertexAttributes_vector.push_back(new VertexAttribute{ index, size, type, normalized, stride, pointer });
		}
		void setAttributes();
		void enableAttributes();
		void disableAttributes();

		std::vector<VertexAttribute*>::iterator begin() { return vertexAttributes_vector.begin(); }
		std::vector<VertexAttribute*>::iterator end() { return vertexAttributes_vector.end(); }

	public:
		static inline std::shared_ptr<VertexAttributes> create() { 
			return std::make_shared<VertexAttributes>(); 
		}
	};
}