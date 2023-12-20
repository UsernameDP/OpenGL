#include "pch.hpp"
#include "AssetPool.hpp"

#include "GLCore/util/FileHandler.hpp"

namespace GLCore::Extension {

	std::unique_ptr<AssetPool> AssetPool::instance = nullptr;

	AssetPool::~AssetPool() {
		for (auto& pair : AssetPool::GLSL_SRCS) {
			delete pair.second;
		}
		AssetPool::GLSL_SRCS.clear();
	}

	void AssetPool::init() {
		if (instance == nullptr) {
			instance = std::make_unique<AssetPool>();
		}
		else {
			LOG_WARN("AssetPool instance already exists");
		}
	}

	std::string& AssetPool::getGLSL_SRC(const std::string& relativePath) {
		std::string* GLSL_SRC = AssetPool::GLSL_SRCS.at(relativePath);

		if (GLSL_SRC == nullptr) {
			GLSL_SRC = new std::string(util::FileHandler::readFile(relativePath));
		}

		return *GLSL_SRC;
	}

}