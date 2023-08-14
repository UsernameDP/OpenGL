#include "pch.hpp"
#include "GLCore/Core/Application.hpp"
#include "Camera.hpp"
#include <cmath>


namespace GLCore::Uniforms {
	CameraSettings::CameraSettings(
		const float& mouseSensitivity,
		const float& cameraSpeedMag
	) {
		this->mouseSensitivity = mouseSensitivity;
		this->cameraSpeedMag = cameraSpeedMag;
		this->cameraSpeed = 0;
	}
	/*-----------------------------------------------------------------*/
	Camera::Camera(const CameraSettings& settings) {
		this->settings = settings;
	}

	void Camera::move(const glm::vec3& cameraPos) {
		this->cameraPos = cameraPos;
	}
	void Camera::face(const float& yaw, const float& pitch) {
		this->yaw = yaw;
		this->pitch = pitch;

		if (pitch_limit) { //the limit exists here b/c this->cameraFront should not be updated 
			if (this->pitch > pitch_limit) {
				this->pitch = pitch_limit - 0.01f;
			}
			else if (this->pitch < -pitch_limit) {
				this->pitch = -pitch_limit + 0.01f;
			}
		}

		glm::vec3 direction;
		direction.x = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
		direction.y = sin(glm::radians(this->pitch));
		direction.z = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));

		this->cameraFront = glm::normalize(direction);
	}


	void Camera::onUpdate(const TimeStep& ts) {
		settings.cameraSpeed = settings.cameraSpeedMag * ts.getDeltaSeconds();

		if (walkAround_with_keyboard) {
			if (Application::getKey(GLFW_KEY_W, true)) {
				moveDelta(settings.cameraSpeed * cameraFront);
			}
			if (Application::getKey(GLFW_KEY_S, true)) {
				moveDelta(-settings.cameraSpeed * cameraFront);
			}
			if (Application::getKey(GLFW_KEY_D, true)) {
				moveDelta(glm::normalize(glm::cross(cameraFront, cameraUp)) * settings.cameraSpeed);
			}
			if (Application::getKey(GLFW_KEY_A, true)) {
				moveDelta(-glm::normalize(glm::cross(cameraFront, cameraUp)) * settings.cameraSpeed);
			}
		}

		if (lookAround_with_mouse) {
			glm::vec2 mouseDelta = Application::getMouseDelta(true, lookAround_with_rightClick_mouse) * settings.mouseSensitivity;
			faceDelta(mouseDelta.x, -mouseDelta.y);
		}
	}
}