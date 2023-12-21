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
		for (auto& pair : AssetPool::shaders) {
			delete pair.second;
		}
		AssetPool::shaders.clear();
		for (auto& pair : AssetPool::computeShaders) {
			delete pair.second;
		}
		AssetPool::computeShaders.clear();
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
		std::string* GLSL_SRC = AssetPool::instance->GLSL_SRCS.at(relativePath);

		if (GLSL_SRC == nullptr) {
			GLSL_SRC = new std::string(util::FileHandler::readFile(relativePath));
		}

		return *GLSL_SRC;
	}
	Shaders::Shader& AssetPool::getShader(const std::string& name)
	{
		Shaders::Shader* shader = AssetPool::instance->shaders.at(name);
		if (shader == nullptr) {
			LOG_ERROR("{0} shader needs to be set before", name);
		}

		return *shader;
	}
	void AssetPool::setShader(Shaders::Shader* shader)
	{
		AssetPool::instance->shaders[shader->getName()] = shader;
	}
	Shaders::ComputeShader& AssetPool::getComputeShader(const std::string& name)
	{
		Shaders::ComputeShader* shader = AssetPool::instance->computeShaders.at(name);
		if (shader == nullptr) {
			LOG_ERROR("{0} shader needs to be set before", name);
		}

		return *shader;
	}
	void AssetPool::setComputeShader(Shaders::ComputeShader* shader)
	{
		AssetPool::instance->computeShaders[shader->getName()] = shader;
	}
}