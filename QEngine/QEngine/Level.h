#pragma once
#include "LinkedList.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Physics.h"
#include "lualib.h"
#include "luabridge.h"

using namespace glm;
using namespace luabridge;

namespace QEngine
{
	class Level
	{
	public:
		Level(string name, lua_State* L);
		~Level();

	private:
		LinkedList<GameObject>* gameObjects;
		string name;

	public:
		Physics* physics;

	public:
		void Initialise();
		void Update();

		string GetName();
	};
}