#pragma once
#include "Component.h"
#include "lua.hpp"
#include "luabridge.h"
#include "GameObject.h"

#include <string>
#include <iostream>

#include <btKinematicCharacterController.h>

using namespace std;
using namespace glm;
using namespace luabridge;

namespace QEngine
{
	class PlayerController : public Component
	{
	public:
		PlayerController();
		PlayerController(GameObject* gameObject, btKinematicCharacterController* pController);
		~PlayerController();

	public:
		void Initialise();
		void Update();

	private:
		btVector3 direction;
		btVector3 forwardDir;
		btVector3 strafingDir;

	public:
		btKinematicCharacterController* controller;

		void MoveForward(int dir, float Speed);
		void MoveLeft(int dir, float Speed);

	public:
		static void Register(lua_State* L)
		{
			getGlobalNamespace(L)
				.beginNamespace("QEngine")
					.beginClass<PlayerController>("PlayerController")
						.addFunction("MoveForward", &PlayerController::MoveForward)
						.addFunction("MoveLeft", &PlayerController::MoveLeft)
					.endClass()
				.endNamespace();
		}
	};
}