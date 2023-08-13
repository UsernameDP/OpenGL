#pragma once
#include "../Extension.hpp"
#include "../Shaders/Shader.hpp"
#include "GLCore/Core/TimeStep.hpp"

namespace GLCore::Uniforms {
	struct CameraSettings {
		float mouseSensitivity;
		float cameraSpeedMag;
		float cameraSpeed;

		CameraSettings(
			const float& mouseSensitivity = 0.1f,
			const float& cameraSpeedMag = 2.5f
		);
	};
	/*-----------------------------------------------------------------*/

	class Camera {
	private:
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		glm::mat4 MVC;

		CameraSettings settings;

		float yaw = -90.0f; //theta X
		float pitch = 0.0f; //theta Y
	private:
		//Options
		bool walkAround_with_keyboard = false;
		bool lookAround_with_mouse = false;
		bool lookAround_with_rightClick_mouse = false;
		float pitch_limit = false; //false == 0
	public:
		Camera() = default;
		Camera(const CameraSettings& settings);
		virtual ~Camera() = default;


		void move(const glm::vec3& cameraPos);
		inline void moveDelta(const glm::vec3& deltaDistance) {
			move(this->cameraPos + deltaDistance);
		}
		void face(const float& yaw, const float& pitch);
		inline void faceDelta(const float& deltaYaw, const float& deltaPitch) {
			face(this->yaw + deltaYaw, this->pitch + deltaPitch);
		}

		virtual void onUpdate(const TimeStep& ts); //run onUpdate() before running any function


		inline void setModel(glm::mat4 model) { this->model = model; }
		inline void setView(
			const glm::vec3& cameraPos, 
			const glm::vec3& cameraFront, 
			const glm::vec3& cameraUp) { 
			this->cameraPos = cameraPos;
			this->cameraFront = cameraFront;
			this->cameraUp = cameraUp;			
		}
		inline void setProjection(const glm::mat4& projection) { this->projection = projection; }
		inline void setCameraSettings(const CameraSettings& settings) { this->settings = settings; }
		
		inline void updateView() { this->view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); }
		inline void updateMVC() { this->MVC = this->projection * this->view * this->model; }

		inline void uploadModel(Shaders::Shader* shader, const std::string& name = "model") { shader->uploadMat4f(name, model, false); };
		inline void uploadView(Shaders::Shader* shader, const std::string& name = "view") { shader->uploadMat4f(name, view, false); };
		inline void uploadProjection(Shaders::Shader* shader, const std::string& name = "projection") { shader->uploadMat4f(name, projection, false); };
		inline void uploadCamera(Shaders::Shader* shader, const std::string& name = "MVC") { shader->uploadMat4f(name, this->MVC, true); }
	public:
		inline void enable_walkAround_with_keyboard(bool enable = true){ 
			walkAround_with_keyboard = enable;
		}
		inline void enable_lookAround_with_mouse(bool enable = true) {
			lookAround_with_mouse = enable;
		}
		inline void enable_lookAround_with_rightClick_mouse(bool enable = true) { //lookAround_with_mouse also needs to be enabled
			lookAround_with_rightClick_mouse = enable;
		}
		inline void limit_pitch_to(const float& angle = 90.0f) {
			pitch_limit = angle;
		}
	};
}