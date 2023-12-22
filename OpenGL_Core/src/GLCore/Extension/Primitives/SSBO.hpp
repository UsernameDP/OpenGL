#pragma once
#include "GLBufferObject.hpp"
#include "GLDetachableInterface.hpp"
#include "GLBindableAtInterface.hpp"

namespace GLCore::Extension::Primitives {
	class SSBO : public GLBufferObject, public GLDetachableInterface, public GLBindableAtInterface {
	private:
		size_t SIZE;
		unsigned long int SIZE_WITH_DATATYPE; // = SIZE * sizeof(DATATYPE)
		GLenum DRAW_TYPE;

		//Multiple Array Upload Members
		unsigned long int MULTIPLE_BUFFER_OFFSET = NULL;
	public:

		/*When uploading one array only */
		template<typename T>
		SSBO(const GLenum& DRAW_TYPE,
			const size_t& SIZE,
			std::vector<T>* data
		) : GLBufferObject(GL_SHADER_STORAGE_BUFFER) {
			this->DRAW_TYPE = DRAW_TYPE;
			this->SIZE = SIZE;
			this->SIZE_WITH_DATATYPE = sizeof(T) * static_cast<unsigned int>(SIZE);

			glGenBuffers(1, &ID);
			bind();
			glBufferData(GL_SHADER_STORAGE_BUFFER, this->SIZE_WITH_DATATYPE, data->data(), this->DRAW_TYPE);
			unbind();
		}
		SSBO(const GLenum& _DRAW_TYPE, const size_t SIZE, const size_t& SIZE_WITH_DATATYPE);

		/*Uploading multiple DEFINITE SIZED arrays*/
		void resetOffset();
		template<typename T>
		inline void uploadSubData(const std::vector<T>* data, const unsigned int& offset_input = NULL) {
			if (offset_input != NULL) {
				this->MULTIPLE_BUFFER_OFFSET = offset_input;
			}

			const unsigned long int size_with_dataType = sizeof(T) * static_cast<unsigned int>(data->size());

			bind();
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, MULTIPLE_BUFFER_OFFSET, size_with_dataType, data->data());

			this->MULTIPLE_BUFFER_OFFSET += size_with_dataType;
		}

		/*-------------------------------------------------------------*/

		void bindAt(const GLuint& loc = 0) override;
		void detach() override;
		void destroy() override;

		//Reading single array SSBOs
		template<typename T>
		inline void readDataTo(std::vector<T>* destination, const int& startIndx = -1, const int& endIndx = -1) {			
			bind(); //determines which SSBO to read from
			//Map the buffer object's memory in the GPU into the GPU's address space
			void* mappedBuffer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
			if (mappedBuffer) {
				//exd::memcpy_SubVector_from_Array(mappedBuffer, this->SIZE, destination, startIndx, endIndx);
			}
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

			unbind();
		}
		//Reading multiple array SSBOs
		
	};
}