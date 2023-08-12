#pragma once
#include "../Extension.hpp"

namespace GLCore::Primitives {
	class Texture {
	private:
		int width, height;
		int nrChannels; //1 Channel = grayScale, 3 Channels = RGB, 4 Channels = RGBA
		unsigned int ID;
		unsigned char* data;
		std::string path;
	private:
		virtual void texParameters();
	public:
		static GLint MAXTextureUnits;
	public:
		Texture() = default; //for CustomTextures (for ComputeShaders)
		Texture(const std::string& relativePath, const GLuint& format = NULL, const GLuint& internalFormat = NULL);
		~Texture();

		void bind(const unsigned int& slot = 0);
		void unbind();
	};
	
}