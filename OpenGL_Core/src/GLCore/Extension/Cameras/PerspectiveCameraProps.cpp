#include "pch.hpp"
#include "PerspectiveCameraProps.hpp"

namespace GLCore::Extension::Cameras {
	PerspectiveCameraProps::PerspectiveCameraProps(const glm::vec3& cameraPos, const float& pitch, const float& yaw, const glm::vec3& cameraUp, const float& initFOV, const float& nearDist, const float& farDist)
	{
		this->cameraPos = cameraPos;
		this->pitch = pitch;
		this->yaw = yaw;
		this->cameraUp = cameraUp;
		this->initFOV = initFOV;
		this->nearDist = nearDist;
		this->farDist = farDist;

		this->FOV = this->initFOV;
	}

	PerspectiveCameraProps::PerspectiveCameraProps(const float& radius, const float& angleV, const float& angleH, const glm::vec3& cameraTarget, const glm::vec3& cameraUp, const float& initFOV, const float& nearDist, const float& farDist)
	{
		this->radius = radius;
		this->angleV = angleV;
		this->angleH = angleH;
		this->cameraTarget = cameraTarget;
		this->cameraUp = cameraUp;
		this->nearDist = nearDist;
		this->farDist = farDist;
		this->initFOV = initFOV;

		this->FOV = this->initFOV;
	}

}