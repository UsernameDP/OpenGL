#pragma once
#include "../Extension.hpp"

namespace GLCore::Primitives {
	class SSBO {
	private:
		GLuint SSBOID = 0;
		size_t SIZE;
		unsigned long int SIZE_WITH_DATATYPE; // = SIZE * sizeof(DATATYPE)
		GLenum _DRAW_TYPE;
		
		//Members for batch uploads:
		GLvoid* batchedData = nullptr;
		unsigned long int BATCH_OFFSET_WITH_DATATYPE = 0;

	public:
		SSBO operator=(const SSBO&) = delete; //Prevents copy assignment, since &SSBOID matters

		SSBO() = default;
		/*When uploading one array only */
		template<typename T>
		SSBO(const GLenum& _DRAW_TYPE,
			const size_t& SIZE,
			std::vector<T>* data = nullptr
		) {
			this->_DRAW_TYPE = _DRAW_TYPE;
			this->SIZE = SIZE;
			this->SIZE_WITH_DATATYPE = sizeof(T) * static_cast<unsigned int>(SIZE);

			glGenBuffers(1, &SSBOID);
			BasicBind();
			
			if (data == nullptr) {
				glBufferData(GL_SHADER_STORAGE_BUFFER, this->SIZE_WITH_DATATYPE, nullptr, this->_DRAW_TYPE);
			}
			else {
				glBufferData(GL_SHADER_STORAGE_BUFFER, this->SIZE_WITH_DATATYPE, data->data(), this->_DRAW_TYPE);
			}

			BasicUnbind();
		}
		~SSBO(); //for smart_ptr instantiations

		/*Uploading multiple arrays*/
		void createBatchData(); //Mapping
		template<typename T>
		void uploadToBatch(const std::vector<T>& data) { //parameters for memcpy
			unsigned long int DATA_SIZE_WITH_DATATYPE = data.size() * sizeof(T);
			BATCH_OFFSET_WITH_DATATYPE += DATA_SIZE_WITH_DATATYPE;
			
			memcpy(reinterpret_cast<char*>(batchedData) + BATCH_OFFSET_WITH_DATATYPE,
				data.data(),
				DATA_SIZE_WITH_DATATYPE
			);
		} 
		void destroyBatchData(); //UnMapping

		/*-------------------------------------------------------------*/

		void BasicBind();
		void bind(const unsigned int& bindIndx = 0);
		void BasicUnbind();
		void unbind();
		void destroy();

		template<typename T>
		void readDataTo(std::vector<T>* destination) {
			BasicBind(); //determines which SSBO to read from

			//Map the buffer object's memory in the GPU into the GPU's address space
			void* mappedBuffer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
			if (mappedBuffer) {
				if (destination->size() != this->SIZE) destination->resize(this->SIZE);

				

				memcpy(destination->data(), mappedBuffer, this->SIZE_WITH_DATATYPE);
			}
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

			BasicUnbind();
		}

		//Delete create() and have two different constructors also use templates to upload data
		
	};
}