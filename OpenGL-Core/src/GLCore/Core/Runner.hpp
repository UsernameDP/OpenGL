#pragma once
#include "Core.hpp"
#include "Application.hpp"
#include "GLCore/Extension/Util/AssetPool.hpp"

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
			
			Util::AssetPool::init();
			try { //In constructor, try creating app
				app = std::make_unique<T>(name, width, height, backgroundColor);
				app->init();
			}
			catch (const std::exception e) {
				std::cout << TextColor::RED << "App Instantiate Exception : " << e.what() << std::endl << TextColor::RESET;
				failedToCreate = true;
			}
		}

		void run() {
			if (!failedToCreate) {
				try {
					app->run();
				}
				catch (const std::exception e) {
					std::cout << TextColor::RED << "App Running Exception : " << e.what() << std::endl << TextColor::RESET;
				}
			}

			LOG("Runner has ended");
		}

	};
}