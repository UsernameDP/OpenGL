#include "pch.hpp"
#include "AssetPool.hpp"

namespace GLCore::util {
	AssetPool::~AssetPool() {
		for (auto pair : GLSLSrcs) {
			delete pair.second;
		}
		for (auto pair : Shaders) {
			delete pair.second;
		}

		LOG_DESTRUCTOR("AssetPool");
	}

	void AssetPool::init() {
		s_Instance = std::make_unique<AssetPool>();
	}

	std::string* AssetPool::getGLSLSrc(const std::string& path) {
		//cwd (current working directory) aka. which project directory the program is ran / debugged
		std::filesystem::path cwd = std::filesystem::current_path();
		std::filesystem::path solutionPath = cwd.parent_path();
		std::filesystem::path GLSLSrcPath = solutionPath / path;

		LOG("GLCore::util::AssetPool::getGLSLSrc(" + GLSLSrcPath.string() + ")");

		std::string* GLSLSrc = get()->GLSLSrcs[GLSLSrcPath];
		if (!GLSLSrc) {
			GLSLSrc = new std::string(exd::readFile(GLSLSrcPath.string()));
			get()->GLSLSrcs[GLSLSrcPath] = GLSLSrc;
		}

		return GLSLSrc;
	}
	Shaders::Shader* AssetPool::getShader(const std::string& name) {
		LOG("GLCore::util::AssetPool::getShader(" + name + ")");
		Shaders::Shader* foundShader = get()->Shaders[name];
		if (!foundShader) {
			THROW_RUNTIME_ERROR(name + "<Shader> has yet to be set via. setShader(Shader*)");
		}

		return foundShader;
	}

	void AssetPool::setShader(Shaders::Shader* shader) {
		get()->Shaders[shader->getName()] = shader;
	}

	std::unique_ptr<AssetPool> AssetPool::s_Instance = nullptr;
}