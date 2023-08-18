#pragma once

#include "Component.h"
#include "GameObject.h"
#include "lua.hpp"
#include "luabridge.h"

using namespace std;
using namespace luabridge;

namespace QEngine 
{
	class Script : public Component
	{
	public:
		Script(GameObject* gameObject, const char* scriptName, lua_State* L);

	private:
		lua_State* L;

		LuaRef* componentScript;

		LuaRef* OnCollisionEnterScript;
		LuaRef* OnCollisionExitScript;
		LuaRef* OnStartScript;
		LuaRef* OnUpdateScript;

	public:
		void Initialise();
		void Update();

		void Invoke(char* function);
		void OnCollisionEnter(GameObject* collider);
		void OnCollisionExit(GameObject* collider);
	};
}