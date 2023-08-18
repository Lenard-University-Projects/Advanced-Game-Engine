#include "stdafx.h"
#include "Graphics.h"
#include "Camera.h"

namespace QEngine 
{
	int Graphics::DEFAULT_WINDOW_WIDTH = 1200;
	int Graphics::DEFAULT_WINDOW_HEIGHT = 800;

	mat4 Graphics::projectionMatrix;
	Camera* Graphics::mainCamera = 0;
	Light* Graphics::mainLight = 0;

	void Graphics::SetLight(Light* light)
	{
		mainLight = light;
	}

	Light* Graphics::GetLight()
	{
		return mainLight;
	}

	mat4 Graphics::GetProjectionMatrix()
	{
		return projectionMatrix;
	}

	Camera* Graphics::GetMainCamera()
	{
		return mainCamera;
	}

	void Graphics::SetMainCamera(Camera * camera)
	{
		mainCamera = camera;

		float aspectRatio = Graphics::DEFAULT_WINDOW_WIDTH / (float)Graphics::DEFAULT_WINDOW_HEIGHT;

		projectionMatrix = frustum(-aspectRatio * camera->GetNearPlane(), aspectRatio * camera->GetNearPlane(), -camera->GetNearPlane(), camera->GetNearPlane(), camera->GetNearPlane(), camera->GetFarPlane());

		// Optional
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glEnable(GL_DEPTH_TEST);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();


		// left, right, bottom, top, near, far
		glFrustum(-aspectRatio * camera->GetNearPlane(), aspectRatio * camera->GetNearPlane(), -camera->GetNearPlane(), camera->GetNearPlane(), camera->GetNearPlane(), camera->GetFarPlane());
	}
}
