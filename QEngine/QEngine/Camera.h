#pragma once
#include "component.h"
#include "GameObject.h"
#include "Graphics.h"
#include "lua.hpp"
#include "luabridge.h"

using namespace glm;
using namespace luabridge;

namespace QEngine
{
	class Camera : public Component
	{
	public:
		Camera(GameObject* gameObject, float nearPlane, float farPlane);
		~Camera();

	private:
		float farPlane;
		float nearPlane;

		float cameraPitch;
		float cameraYaw;

		vec3 up;
		vec3 viewDirection;

		mat4x4 viewMatrix;
		mat4x4 rotationMatrix;
		mat4x4 rollMatrix;
	public:
		void Initialise();
		void Update();

		float GetFarPlane();
		float GetNearPlane();

		// Invoked by LUA scripts
		void Yaw(float value);
		void Pitch(float value);
		void Zoom(float value);

		// Used by shaders that draw the vertices
		mat4x4 GetViewMatrix();

	public:
		static void Register(lua_State* L)
		{
			getGlobalNamespace(L)
				.beginNamespace("QEngine")
				.beginClass<Camera>("Camera")
				.addFunction("Yaw", &Camera::Yaw)
				.addFunction("Pitch", &Camera::Pitch)
				.addFunction("Zoom", &Camera::Zoom)
				.endClass()
				.endNamespace();
		}
	};
}

