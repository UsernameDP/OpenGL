#pragma once
#include "../Extension.hpp"
#include "util/FileHandler.hpp"
#include "GLCore/Extension/Shaders/Shader.hpp"
#include <filesystem>

namespace GLCore::util {
	class AssetPool {
	private:
		static std::unique_ptr<AssetPool> s_Instance;
	private:
		std::unordered_map<std::filesystem::path, std::string*> GLSLSrcs;
		std::unordered_map<std::string, Shaders::Shader*> Shaders;
	private:
		static inline AssetPool* get() { return s_Instance.get(); }
	public:
		AssetPool() { LOG_CONSTRUCTOR("AssetPool"); }
		~AssetPool();
	public:
		static void init();
		static std::string* getGLSLSrc(const std::string& path);
		static Shaders::Shader* getShader(const std::string& name);

		static void setShader(Shaders::Shader* shader);
	};
}