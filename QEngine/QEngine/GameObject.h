#pragma once
#include "glew.h"
#include "glut.h"
#include "Object.h"
#include "LinkedList.h"
#include "Component.h"
#include "Transform.h"
#include "RigidBody.h"
#include "lua.hpp"
#include "luabridge.h"

#include <string>
#include <iostream>

using namespace std;
using namespace luabridge;

namespace QEngine 
{
	class PlayerController;
	class Script;

	class GameObject : public Object
	{
	private:
		bool active;
		string name;
		string tag;

		Transform* transform;
		RigidBody* rigidBody;
		PlayerController* playerController;
		Script* script;

	public:
		LinkedList<Component>* components;
		GameObject* next;

	public:
		~GameObject();

		GameObject(string name, string tag, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3  scale = glm::vec3(1, 1, 1));
		GameObject(string name);

	public:
		void Destroy();
		void Initialise();
		bool IsActive();
		void Update();

		void SetTag(string tag);
		void AddComponent(Component* component);

	public:
		string GetName();
		string GetTag();

		Transform*			GetTransform();
		RigidBody*			GetRigidBody();
		PlayerController*	GetPlayerController();
		Script*				GetScript();

	public:
		static void Register(lua_State* L)
		{
			getGlobalNamespace(L)
				.beginNamespace("QEngine")
					.beginClass<Object>("Object")
						.addFunction("GetID", &Object::GetID)
					.endClass()
					.deriveClass<GameObject, Object>("GameObject")
						.addFunction("GetName", &GameObject::GetName)
						.addFunction("GetTag", &GameObject::GetTag)
						.addFunction("Destroy", &GameObject::Destroy)
						.addFunction("GetTransform", &GameObject::GetTransform)
						.addFunction("GetRigidBody", &GameObject::GetRigidBody)
						.addFunction("GetPlayerController", &GameObject::GetPlayerController)
					.endClass()
				.endNamespace();
		}
	};
}
