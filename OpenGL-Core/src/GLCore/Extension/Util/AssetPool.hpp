#pragma once
#include "../Extension.hpp"
#include "util/FileHandler.hpp"
#include "GLCore/Extension/Shaders/Shader.hpp"
#include "GLCore/Extension/Primitives/Texture.hpp"
#include <filesystem>

namespace GLCore::util {
	class AssetPool {
	private:
		static std::unique_ptr<AssetPool> s_Instance;
	private:
		std::unordered_map<std::string, std::string*> GLSLSrcs;
		std::unordered_map<std::string, Primitives::Texture*> textures;
		std::unordered_map<std::string, Shaders::Shader*> Shaders;
	private:
		static inline AssetPool* get() { return s_Instance.get(); }
	public:
		AssetPool() { LOG_CONSTRUCTOR("AssetPool"); }
		~AssetPool();
	public:
		static void init();
		static std::string* getGLSLSrc(const std::string& relativePath);
		static Primitives::Texture* getTexture(const std::string& relativePath);
		static Shaders::Shader* getShader(const std::string& name);

		static inline void setGLSLSrc(const std::string& relativePath, const std::string& content) {
			LOG("GLCore::util::AssetPool::setGLSLSrc(" + relativePath + ",\n" + content + "\n)");
			get()->GLSLSrcs[relativePath] = new std::string(content);
		}

		static inline void setTexture(const std::string& relativePath, Primitives::Texture* texture) {
			LOG("GLCore::util::AssetPool::setTexture(" + relativePath + ")");
			get()->textures[relativePath] = texture;
		}

		static inline void setShader(Shaders::Shader* shader) {
			LOG("GLCore::util::AssetPool::setShader(" + shader->getName() + ")");
			get()->Shaders[shader->getName()] = shader;
		}
	};
}