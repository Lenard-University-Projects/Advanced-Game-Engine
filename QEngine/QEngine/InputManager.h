#pragma once

#include "lua.hpp"
#include "luabridge.h"
#include "glfw3.h"
#include "glm.hpp"
#include <map>
#include <string>

using namespace std;
using namespace glm;
using namespace luabridge;

namespace QEngine
{	
	// Cursor's scree coordinates on the screen
	struct Position {
		double x, y;
	};

	class InputManager
	{
	private:
		static GLFWwindow* window;
		static map<string, int > keyMappings;

		static Position currentCursor;
		static Position previousCursor;

		// There is no GLFW constant to represent mouse movement along x axis so define here
		static const int MERLIN_MOUSE_MOVE_X = 10001;

	public:
		static void Initialise(GLFWwindow* win) 
		{
			window = win;
			keyMappings["CameraZoomIn"]		= GLFW_KEY_PAGE_UP;
			keyMappings["CameraZoomOut"]	= GLFW_KEY_PAGE_DOWN;

			keyMappings["CameraYawLeft"]	= GLFW_KEY_LEFT;
			keyMappings["CameraYawRight"]	= GLFW_KEY_RIGHT;
			keyMappings["CameraPitchUp"]	= GLFW_KEY_UP;
			keyMappings["CameraPitchDown"]	= GLFW_KEY_DOWN;

			keyMappings["Forward"]		= GLFW_KEY_W;
			keyMappings["Backwards"]	= GLFW_KEY_S;
			keyMappings["Left"]			= GLFW_KEY_A;
			keyMappings["Right"]		= GLFW_KEY_D;

			keyMappings["Xaxis"]			= MERLIN_MOUSE_MOVE_X;
		}

		static bool GetKey(string key) 
		{
			if (glfwGetKey(window, keyMappings[key]) == GLFW_PRESS) 
				return true;

			return false;
		}

		static void RecordLastCursorPosition() 
		{
			glfwGetCursorPos(window, &previousCursor.x, &previousCursor.y);
		}

		static float GetAxis(string key) 
		{
			if (keyMappings[key] == MERLIN_MOUSE_MOVE_X) 
			{
				glfwGetCursorPos(window, &currentCursor.x, &currentCursor.y);
				return clamp(float(currentCursor.x - previousCursor.x), -1.0f, 1.0f);
			}
			else return 0.0f;
		}


		static void Register(lua_State* L) 
		{
			getGlobalNamespace(L)
				.beginNamespace("QEngine")
				.beginClass<InputManager>("InputManager")
				.addStaticFunction("GetKey", &InputManager::GetKey)
				.addStaticFunction("GetAxis", &InputManager::GetAxis)
				.endClass()
				.endNamespace();
		}
	};
}