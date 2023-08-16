#pragma once
#include "../Extension.hpp"
#include "util/PrimitiveTypeHandler.hpp"

namespace GLCore::Primitives {
	class SSBO {
	private:
		GLuint SSBOID = 0;
		size_t SIZE;
		unsigned long int SIZE_WITH_DATATYPE; // = SIZE * sizeof(DATATYPE)
		GLenum _DRAW_TYPE;

		//Multiple Array Upload Members
		unsigned long int MULTIPLE_BUFFER_OFFSET = NULL;

	public:
		SSBO operator=(const SSBO&) = delete; //Prevents copy assignment, since &SSBOID matters

		SSBO() = default;
		/*When uploading one array only */
		template<typename T>
		SSBO(const GLenum& _DRAW_TYPE,
			const size_t& SIZE,
			std::vector<T>* data
		) {
			this->_DRAW_TYPE = _DRAW_TYPE;
			this->SIZE = SIZE;
			this->SIZE_WITH_DATATYPE = sizeof(T) * static_cast<unsigned int>(SIZE);

			glGenBuffers(1, &SSBOID);
			BasicBind();
			glBufferData(GL_SHADER_STORAGE_BUFFER, this->SIZE_WITH_DATATYPE, data->data(), this->_DRAW_TYPE);
			BasicUnbind();
		}
		SSBO(const GLenum& _DRAW_TYPE, const size_t SIZE, const size_t& SIZE_WITH_DATATYPE);

		~SSBO(); //for smart_ptr instantiations

		/*Uploading multiple arrays*/
		void resetOffset();
		template<typename T>
		inline void uploadSubData(const std::vector<T>* data, const unsigned int& offset_input = NULL) {
			if (offset_input != NULL) {
				this->MULTIPLE_BUFFER_OFFSET = offset_input;
			}

			const unsigned long int size_with_dataType = sizeof(T) * static_cast<unsigned int>(data->size());

			BasicBind();
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, MULTIPLE_BUFFER_OFFSET, size_with_dataType, data->data());

			this->MULTIPLE_BUFFER_OFFSET += size_with_dataType;
		}

		/*-------------------------------------------------------------*/

		void BasicBind();
		void bind(const unsigned int& bindIndx = 0);
		void BasicUnbind();
		void unbind();
		void destroy();

		//Reading single array SSBOs
		template<typename T>
		inline void readDataTo(std::vector<T>* destination, const int& startIndx = -1, const int& endIndx = -1) {			
			BasicBind(); //determines which SSBO to read from
			//Map the buffer object's memory in the GPU into the GPU's address space
			void* mappedBuffer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
			if (mappedBuffer) {
				exd::memcpy_SubVector_from_Array(mappedBuffer, this->SIZE, destination, startIndx, endIndx);
			}
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

			BasicUnbind();
		}
		//Reading multiple array SSBOs
		
	};
}