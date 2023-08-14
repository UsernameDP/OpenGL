#pragma once
#include "Application.hpp"
#include "GLCore/Extension/util/AssetPool.hpp"

#include "OpenGLDebug.hpp"

namespace GLCore {
	template <typename T, typename = std::enable_if_t<std::is_base_of_v<Application, T>>>
	class Runner {
	private:
		std::unique_ptr<T> app = nullptr;
		bool failedToCreate = false;

	public:
		Runner(const std::string& name = "GLFW Window",
			uint32_t width = 1280, uint32_t height = 720,
			glm::vec4 backgroundColor = glm::vec4(0.0, 0.0, 0.0, 0.0)){

			LOG("Runner has started");
			
			util::AssetPool::init();
			try { //In constructor, try creating app
				app = std::make_unique<T>(name, width, height, backgroundColor);
#ifdef VERSION_DEBUG
				enableGLDebugging();
#endif
				app->init();
			}
			catch (const std::exception e) {
				std::cout << "App Instantiate Exception : " << e.what() << std::endl;
				failedToCreate = true;
			}
		}

		void run() {
			if (!failedToCreate) {
				try {
					app->run();
				}
				catch (const std::exception e) {
					std::cout << "App Running Exception : " << e.what() << std::endl;
				}
			}

			LOG("Runner has ended");
		}

	};
}