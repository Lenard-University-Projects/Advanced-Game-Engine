#include "stdafx.h"
#include "Camera.h"
#include "GameObject.h"

namespace QEngine
{
	Camera::Camera(GameObject * gameObject, float nearPlane, float farPlane) :Component(gameObject)
	{
		this->nearPlane		= nearPlane;
		this->farPlane		= farPlane;
		this->gameObject	= gameObject;

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		int screenWidth		= viewport[2];
		int screenHeight	= viewport[3];
		float aspectRatio	= screenWidth / (float)screenHeight;

		viewDirection = vec3(0, 0, 0);
		up = vec3(0, 1, 0);
	}

	Camera::~Camera(void) { }

	void Camera::Initialise() { }

	void Camera::Update() 
	{
		vec3 position = gameObject->GetTransform()->GetPosition();
 		vec4 cameraPosition(position, 0.0);

		cameraPosition = rotationMatrix * rollMatrix * cameraPosition;
	}

	float Camera::GetFarPlane()
	{
		return farPlane;
	}

	float Camera::GetNearPlane()
	{
		return nearPlane;
	}

	void Camera::Yaw(float value) 
	{
		cameraYaw -= value;

		if (cameraYaw < 0) 
			cameraYaw += 360;

		if (cameraYaw >= 360) 
			cameraYaw -= 360;

		float yaw = radians(cameraYaw);
		rotationMatrix = rotate(mat4x4(), yaw, up);
	}

	void Camera::Pitch(float value) 
	{
		cameraPitch -= value;

		if (cameraPitch < 0) 
			cameraPitch += 360;

		if (cameraPitch >= 360) 
			cameraPitch -= 360;

		float pitch = radians(cameraPitch);

		// Get the camera position using the Transform component
		vec3 position	= gameObject->GetTransform()->GetPosition();
		vec3 forward	= position;
		vec3 right		= normalize(cross(up, forward));

		rollMatrix = rotate(mat4x4(), -pitch, right);
	}

	void Camera::Zoom(float value) 
	{
		// Get the camera position using the Transform component
		vec3 position = gameObject->GetTransform()->GetPosition();

		position.z += value;

		gameObject->GetTransform()->SetPosition(position);
	}

	mat4x4 Camera::GetViewMatrix()
	{		
		// Get the camera position using the Transform component
		vec3 position = gameObject->GetTransform()->GetPosition();

		// Convert the position so it can be used with a matrix
		vec4 cameraPosition(position, 0.0);

		// Apply rotation to find the camera position
		cameraPosition = rotationMatrix * rollMatrix * cameraPosition;

		return lookAt(vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z), viewDirection, up);
	}
}