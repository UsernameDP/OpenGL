#pragma once
#include "../Extension.hpp"
#include "Util/FileHandler.hpp"
#include <filesystem>

namespace GLCore::Util {
	class AssetPool {
	private:
		static std::unique_ptr<AssetPool> s_Instance;
	private:
		std::unordered_map<std::filesystem::path, std::string*> GLSLSrcs;
	private:
		static inline AssetPool* get() { return s_Instance.get(); }
	public:
		AssetPool() { LOG_CONSTRUCTOR("AssetPool"); }
		~AssetPool();
	public:
		static void init();
		static std::string* getGLSLSrc(const std::string& path);
	};
}