#include "pch.hpp"
#include "Texture.hpp"
#include "stb_image.h"

namespace GLCore::Primitives {
	void Texture::texParameters() {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	}

	Texture::Texture(const std::string& relativePath, const GLuint& format, const GLuint& internalFormat) 
		:path(relativePath){
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		stbi_set_flip_vertically_on_load(true); //enable this if texture is upside down

		texParameters();

		data = stbi_load(relativePath.c_str(), &width, &height, &nrChannels, 0);
		if (!data) {
			THROW_RUNTIME_ERROR("Texture from " + path + "did not successfully load");
		}

		const std::string fileExtension = exd::getFileExtension(path);

		GLuint usingFormat = GL_RGBA;
		GLuint usingInternalFormat = GL_RGBA8;

		if (format != NULL && internalFormat != NULL) {
			usingFormat = format;
			usingInternalFormat = internalFormat;
		}
		else {
			if (fileExtension == ".jpg") {
				usingFormat = GL_RGB;
				usingInternalFormat = GL_RGB8;
			}
			else if (fileExtension == ".png") {
				usingFormat = GL_RGBA;
				usingInternalFormat = GL_RGBA8;
			}
		}

		glTexImage2D(GL_TEXTURE_2D, 0, usingInternalFormat, width, height, 0, usingFormat, GL_UNSIGNED_BYTE, data);
		unbind();

		stbi_image_free(data);

		LOG_CONSTRUCTOR("Texture<path=" + path + ">");
	}
	Texture::~Texture() {
		glDeleteTextures(1, &ID);
		LOG_DESTRUCTOR("Texture<path=" + path + ">");
	}

	void Texture::bind(const unsigned int& slot) {
		static bool MAXTextureUnits_set = false;
		if (!MAXTextureUnits_set) {
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Texture::MAXTextureUnits);
			MAXTextureUnits_set = true;
		}


		if (slot > MAXTextureUnits) {
			std::string message = "Texture Slot<" + std::to_string(slot) + 
				"> is over your MAXTextureUnits< " + std::to_string(Texture::MAXTextureUnits) + ">";
			THROW_RUNTIME_ERROR(message);
		}

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLint Texture::MAXTextureUnits = NULL;
}