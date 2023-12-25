#pragma once
#include "PerspectiveCameraProps.hpp"

namespace GLCore::Extension::Cameras {

	class PerspectiveCamera {
	private:
		PerspectiveCameraProps props;
	public:
		PerspectiveCamera( const PerspectiveCameraProps& props);

		void move(const glm::vec3& pos);
		void moveDelta(const glm::vec3& deltaPos);
		void moveDeltaX(const float& deltaPosX);
		void moveDeltaY(const float& deltaPosY);
		void moveDeltaZ(const float& deltaPosZ);
		
		void rotateYaw(const float& yaw);
		void rotateDeltaYaw(const float& deltaYaw);
		void rotatePitch(const float& pitch);
		void rotateDeltaPitch(const float& deltaPitch);

		void rotateDeltaAngleHorizontalAboutTarget(const float& deltaAngle);
		void rotateDeltaAngleVerticalAboutTarget(const float& deltaAngle);

		void zoomDeltaFov(const float& changeSinceInitialFOV);

		void onUpdate(const TimeStep& ts, const PerspectiveCameraOptions& rotate_option);

		inline PerspectiveCameraProps& getProps() { return props;  }
		inline glm::mat4& getViewProjection() { return props.VP; }
	};

}