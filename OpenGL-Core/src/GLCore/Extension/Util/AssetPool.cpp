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
			fs::path cwd = fs::current_path();
			fs::path solutionPath = cwd.parent_path();
			fs::path absPath = solutionPath / relativePath;

			setGLSLSrc(relativePath, exd::readFile(absPath.string()));
		}

		return get()->GLSLSrcs[relativePath];
	}
	Primitives::Texture* AssetPool::getTexture(const std::string& relativePath) {
		LOG("GLCore::util::AssetPool::getTexture(" + relativePath + ")");
		if (!exd::mapHas(get()->textures, relativePath)) {
			fs::path cwd = fs::current_path();
			fs::path solutionPath = cwd.parent_path();
			fs::path absPath = solutionPath / relativePath;

			setTexture(relativePath, new Primitives::Texture(absPath.string()));
		}

		return get()->textures[relativePath];
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