#include "glpch.hpp"
#include "AssetPool.hpp"

namespace GLCore::Util {
	AssetPool::~AssetPool() {
		for (auto pair : GLSLSrcs) {
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

		std::string* GLSLSrc = get()->GLSLSrcs[GLSLSrcPath];
		if (!GLSLSrc) {
			GLSLSrc = new std::string(readFile(GLSLSrcPath.string()));
			get()->GLSLSrcs[GLSLSrcPath] = GLSLSrc;
		}

		return GLSLSrc;
	}

	std::unique_ptr<AssetPool> AssetPool::s_Instance = nullptr;
}