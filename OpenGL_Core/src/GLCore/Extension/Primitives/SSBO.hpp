#pragma once
#include "GLBufferObject.hpp"
#include "GLBindableAtInterface.hpp"


namespace GLCore::Extension::Primitives {

	class SSBO : public GLBufferObject, public GLBindableAtInterface {

	public:
		template<typename T>
		SSBO(const GLenum& DRAW_TYPE, std::vector<T>* data) : GLBufferObject(GL_SHADER_STORAGE_BUFFER) {
			glGenBuffers(1, &this->ID);
			bind();
			glBufferData(GL_SHADER_STORAGE_BUFFER, data->size() * sizeof(T), data->data(), DRAW_TYPE);
		}

		void bindAt(const GLuint& loc) override;

		template<typename T>
		void updateData(std::vector<T>* data) {
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data->size() * sizeof(T), data->data());
		}
		
	};

}