#pragma once

namespace GLCore::util {
	class AssetPoolINIT_Shaders { //Settings to configure in GLCore::util::AssetPool before running Application
	public:
		virtual void configure() = 0;
	};
	class AssetPoolINIT_GLSLSrcs {
	public:
		virtual void configure() = 0;
	};
	class AssetPoolINIT {
	public:
		virtual void configure() = 0;
	};
}