#pragma once
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "light.h"
#include "lua.hpp"
#include "luabridge.h"

using namespace glm;
using namespace luabridge;

namespace QEngine
{
	class Graphics
	{
	public:
		static int DEFAULT_WINDOW_WIDTH;
		static int DEFAULT_WINDOW_HEIGHT;

	public:
		static class Camera* mainCamera;
		static mat4 projectionMatrix;
		static Light* mainLight;

	public:
		static void SetLight(Light* light);

		static Light* GetLight();

		static mat4 GetProjectionMatrix();

		static class Camera* GetMainCamera();

		static void SetMainCamera(class Camera* camera);

		static void Register(lua_State* L)
		{
			getGlobalNamespace(L)
				.beginNamespace("QEngine")
				.beginClass<Graphics>("Graphics")
				.addStaticFunction("GetCamera", &Graphics::GetMainCamera)
				.endClass()
				.endNamespace();
		}
	};
}

