#include "stdafx.h"
#include <stdlib.h>
#include "glew.h"
#include "glfw3.h"
#include "Graphics.h"
#include "Camera.h"
#include "Physics.h"
#include "Level.h"
#include "InputManager.h"
#include "PlayerController.h"

#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
#include "luabridge.h"

using namespace luabridge;
using namespace QEngine;

#define  QEngine_VERSION "1.0"

QEngine::Level *level;
lua_State* L;

namespace Engine
{
	class GameObject
	{
	private:
		int id;
	public:
		GameObject(int id) :id(id) {}

		bool GetFlag() { return false; }

		static float Square(float x) { return x * x; }

		int GetID() const { return id; }
		void SetID(const int id) { this->id = id; }

		static void Register(lua_State* L)
		{
			getGlobalNamespace(L)
				.beginNamespace("QEngine")
					.beginClass<GameObject>("GameObject")
					.addConstructor<void(*)(int)>()
					.addFunction("GetFlag",			&GameObject::GetFlag)
					.addStaticFunction("Square",	&GameObject::Square)
					.addProperty("id",				&GameObject::GetID, &GameObject::SetID)
				.endClass().endNamespace();
		}
	};
}

void About() 
{
	printf("QEngine Engine Version %s \n", QEngine_VERSION);
}

void InitialiseGLFW()
{
	if (glfwInit() == GL_TRUE) 
	{
		int major, minor, rev;
		glfwGetVersion(&major, &minor, &rev);
		printf("GLFW3 Version %i:%i:%i \n", major, minor, rev);
		printf("PASS... GLFW Initialized. \n");
	}
	else 
	{
		printf("FAILED.. GLFW Initialization failed. \n");
		exit(EXIT_FAILURE);
	}
}

void InitialiseGLEW() 
{
	if (glewInit() != GLEW_OK) 
	{
		printf("FAILED... Unable to Initialize GLEW. \n");
	}
	else 
		printf("PASS... GLEW Initialized. \n");
}

void InitialiseLua()
{
	L = luaL_newstate();

	if (L == NULL)
		printf("FAILED... Unable to allocate memory for LUA Scripting. \n");
	else
		printf("PASS... LUA Scripting state created. \n");

	luaL_openlibs(L);
	Graphics::Register(L);
	GameObject::Register(L);
	InputManager::Register(L);
	Camera::Register(L);
	Transform::Register(L);
	PlayerController::Register(L);
}

void DoRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	level->Update();
}

void DoPhysics(double DeltaTime) 
{
	level->physics->UpdatePhysics(DeltaTime);
}

// Decouples physics and rendering time steps
void GameLoop(GLFWwindow* window) 
{
	// Physics step
	double dt		= Physics::step;
	double previous = glfwGetTime();
	double lag		= 0.0;

	while (!glfwWindowShouldClose(window)) 
	{
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		double current = glfwGetTime();

		// Time elapsed since last frame
		double elapsed = current - previous;

		previous = current;
		lag		 += elapsed;

		// Depending upon frame time 0 or more physics steps per frame.
		while (lag >= dt) 
		{
			DoPhysics(dt);
			lag -= dt;
		}

		DoRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
		InputManager::RecordLastCursorPosition();
	}
}

void Initialise(GLFWwindow* window)
{
	InitialiseGLEW();
	InputManager::Initialise(window);

	InitialiseLua();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Enable anti aliasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create the level
	level = new QEngine::Level("Demo Scene", L);

	// Load the assets
	level->Initialise();
}

void OnError(int error, const char* description) 
{
	fputs(description, stderr);
}

int main() 
{
	glfwSetErrorCallback(OnError);

	About();
	
	InitialiseGLFW();

	GLFWwindow* window = glfwCreateWindow(Graphics::DEFAULT_WINDOW_WIDTH, Graphics::DEFAULT_WINDOW_HEIGHT, "QEngine Engine", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Get the resolution of the primary monitor
	const GLFWvidmode * vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Center our window
	glfwSetWindowPos(window, (vidmode->width - Graphics::DEFAULT_WINDOW_WIDTH) / 2, (vidmode->height - Graphics::DEFAULT_WINDOW_HEIGHT) / 2);

	// Make the OpenGL context current
	glfwMakeContextCurrent(window);

	// Enable v-sync
	glfwSwapInterval(1);

	Initialise(window);
	GameLoop(window);

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}