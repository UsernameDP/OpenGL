#include "pch.hpp"
#include "PerspectiveCamera.hpp"
#include "GLCore/Core/Application.hpp"

namespace GLCore::Extension::Cameras {
	PerspectiveCamera::PerspectiveCamera(const PerspectiveCameraProps& props)
	{
		this->props = props;
	}

	void PerspectiveCamera::move(const glm::vec3& pos)
	{
		props.cameraPos = pos;
	}

	void PerspectiveCamera::moveDelta(const glm::vec3& deltaPos)
	{
		props.cameraPos += deltaPos;
	}

	void PerspectiveCamera::moveDeltaX(const float& deltaPosX)
	{
		props.cameraPos.x += deltaPosX;
	}

	void PerspectiveCamera::moveDeltaY(const float& deltaPosY)
	{
		props.cameraPos.y += deltaPosY;
	}

	void PerspectiveCamera::moveDeltaZ(const float& deltaPosZ)
	{
		props.cameraPos.z += deltaPosZ;
	}

	void PerspectiveCamera::rotateYaw(const float& yaw)
	{
		props.yaw = yaw;
	}

	void PerspectiveCamera::rotateDeltaYaw(const float& deltaYaw)
	{
		props.yaw += deltaYaw;
	}

	void PerspectiveCamera::rotatePitch(const float& pitch)
	{
		props.pitch = pitch;
	}

	void PerspectiveCamera::rotateDeltaPitch(const float& deltaPitch)
	{
		props.pitch += deltaPitch;
	}

	void PerspectiveCamera::rotateDeltaAngleHorizontalAboutTarget(const float& deltaAngle)
	{
		props.angleH += deltaAngle;
	}

	void PerspectiveCamera::rotateDeltaAngleVerticalAboutTarget(const float& deltaAngle)
	{
		props.angleV += deltaAngle;
	}

	void PerspectiveCamera::zoomDeltaFov(const float& changeSinceInitialFOV)
	{
		props.FOV = props.initFOV + changeSinceInitialFOV;

		if (props.FOV < 0.5f)
			props.FOV = 0.5f;
		if (props.FOV > 89.5f)
			props.FOV = 89.5f;
	}

	void PerspectiveCamera::onUpdate(const TimeStep& ts, const PerspectiveCameraOptions& rotate_option)
	{
		WindowProps& windowProps = Application::get().getWindow().getProps();

		if (props.FOVWithScroll) {
			float scrollY = windowProps.getScrollY();
			zoomDeltaFov(-scrollY);
		}

		if (rotate_option == ROTATE_USING_PITCH_YAW) {
			if (props.rotateWithRightClick) {
				if (windowProps.getRightMouseDown()) {
					rotateDeltaYaw(windowProps.getMousePosDeltaX() * props.mouseSensitivity);
					rotateDeltaPitch(-windowProps.getMousePosDeltaY() * props.mouseSensitivity);
				}

			}

			if (props.rotateWithKeys) {
				float rotateSpeed = props.rotateSpeedFactor * ts.getDeltaSeconds();
				if (windowProps.getKeyPressed(props.ROTATE_UP_KEY)) {
					rotateDeltaPitch(rotateSpeed);
				}
				if (windowProps.getKeyPressed(props.ROTATE_DOWN_KEY)) {
					rotateDeltaPitch(-rotateSpeed);
				}
				if (windowProps.getKeyPressed(props.ROTATE_LEFT_KEY)) {
					rotateDeltaYaw(-rotateSpeed);
				}
				if (windowProps.getKeyPressed(props.ROTATE_RIGHT_KEY)) {
					rotateDeltaYaw(rotateSpeed);
				}
			}

			glm::vec3 direction;
			direction.x = cos(glm::radians(props.yaw)) * cos(glm::radians(props.pitch));
			direction.y = sin(glm::radians(props.pitch));
			direction.z = sin(glm::radians(props.yaw)) * cos(glm::radians(props.pitch));
			props.cameraFront = glm::normalize(direction);
			

			if (props.movementWithKeys) {
				float cameraSpeed = props.cameraSpeedFactor * ts.getDeltaSeconds();
				if (windowProps.getKeyPressed(props.MOVE_FORWARD_KEY)) {
					moveDelta(props.cameraFront * cameraSpeed);
				}
				if (windowProps.getKeyPressed(props.MOVE_BACKWARD_KEY)) {
					moveDelta(-props.cameraFront * cameraSpeed);
				}
				if (windowProps.getKeyPressed(props.MOVE_LEFT_KEY)) {
					moveDelta(-glm::normalize(glm::cross(props.cameraFront, props.cameraUp)) * cameraSpeed);
				}
				if (windowProps.getKeyPressed(props.MOVE_RIGHT_KEY)) {
					moveDelta(glm::normalize(glm::cross(props.cameraFront, props.cameraUp)) * cameraSpeed);
				}
			}

			props.view = glm::lookAt(props.cameraPos, props.cameraPos + props.cameraFront, props.cameraUp);
		}
		else {
						
			if (props.rotateAboutCameraTargetWithKeys) {
				float cameraSpeed = props.cameraSpeedFactor * ts.getDeltaSeconds();
				if (windowProps.getKeyPressed(props.ROTATE_ABOUT_CAMERA_TARGET_UP_KEY)) {
					rotateDeltaAngleVerticalAboutTarget(cameraSpeed);
				}
				if (windowProps.getKeyPressed(props.ROTATE_ABOUT_CAMERA_TARGET_DOWN_KEY)) {
					rotateDeltaAngleVerticalAboutTarget(-cameraSpeed);
				}
				if (windowProps.getKeyPressed(props.ROTATE_ABOUT_CAMERA_TARGET_LEFT_KEY)) {
					rotateDeltaAngleHorizontalAboutTarget(cameraSpeed);
				}
				if (windowProps.getKeyPressed(props.ROTATE_ABOUT_CAMERA_TARGET_RIGHT_KEY)) {
					rotateDeltaAngleHorizontalAboutTarget(-cameraSpeed);
				}
			}

			glm::vec3 deltaDistFromTarget;
			deltaDistFromTarget.x = props.radius * cos(glm::radians(props.angleH)) * cos(glm::radians(props.angleV));
			deltaDistFromTarget.y = props.radius * sin(glm::radians(props.angleV));
			deltaDistFromTarget.z = props.radius * sin(glm::radians(props.angleH)) * cos(glm::radians(props.angleV));
			props.cameraPos = deltaDistFromTarget + props.cameraTarget;

			props.view = glm::lookAt(props.cameraPos, props.cameraTarget, props.cameraUp);
		}
		props.projection = glm::perspective(glm::radians(props.FOV), (float)windowProps.getWidth() / (float)windowProps.getHeight(), props.nearDist, props.farDist);

		props.VP = props.projection * props.view;
	}

}