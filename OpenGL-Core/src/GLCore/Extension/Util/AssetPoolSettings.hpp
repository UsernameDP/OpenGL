#pragma once

namespace GLCore::util {

	class AssetPoolSettings { //Settings to configure in GLCore::util::AssetPool before running Application
	public:
		AssetPoolSettings() = default;

		virtual void run() {};
	};
}