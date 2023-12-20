#pragma once

namespace GLCore::Extension {

	class AssetPool {
	private:
		static std::unique_ptr<AssetPool> instance;
	public:
		AssetPool() = default;
		~AssetPool();

	private:
		static std::unordered_map<std::string, std::string*> GLSL_SRCS;

	public:
		static std::string& getGLSL_SRC(const std::string& relativePath);
		static void setGLSL_SRC(const std::string& relativePath, const std::string& GLSL_SRC);
	
		static void init();
	};

}