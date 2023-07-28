#pragma once

namespace GLCore::Util {

	class AssetPoolSettings { //Settings to configure in GLCore::Util::AssetPool before running Application
	public:
		AssetPoolSettings() = default;

		virtual void run() {};
	};
}