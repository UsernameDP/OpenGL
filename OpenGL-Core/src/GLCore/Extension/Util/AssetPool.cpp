#include "pch.hpp"
#include "AssetPool.hpp"

namespace GLCore::util {
	AssetPool::~AssetPool() {
		for (auto& pair : GLSLSrcs) {
			delete pair.second;
		}
		for (auto& pair : Shaders) {
			delete pair.second;
		}

		LOG_DESTRUCTOR("AssetPool");
	}

	void AssetPool::init() {
		s_Instance = std::make_unique<AssetPool>();
	}

	std::string* AssetPool::getGLSLSrc(const std::string& relativePath) {
		LOG("GLCore::util::AssetPool::getGLSLSrc(" + relativePath + ")");
		if (!exd::mapHas(get()->GLSLSrcs, relativePath)) {
			THROW_RUNTIME_ERROR(relativePath + " GLSLSrc has yet to be set via. setGLSLSrc(path, content)");
		}

		std::string* GLSLSrc = get()->GLSLSrcs[relativePath];

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

	std::unique_ptr<AssetPool> AssetPool::s_Instance = nullptr;
}