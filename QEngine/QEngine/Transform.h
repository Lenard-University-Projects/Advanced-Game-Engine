#pragma once
#include "Component.h"
#include "quaternion.hpp"
#include "glm.hpp"
#include "lua.hpp"
#include "luabridge.h"

using namespace glm;
using namespace luabridge;

namespace QEngine
{
	class Transform : public Component
	{
	public:
		static vec3 const FORWARD;
		static vec3 const RIGHT;
		static vec3 const UP;

	public:
		Transform();
		~Transform();

		Transform(class GameObject* gameObject, vec3 position, vec3 rotation, vec3 scale);
	private:
		vec3 position;
		quat rotation;
		vec3 scale;
	public:
		vec3 GetPosition();
		quat GetRotation();
		vec3 GetScale();

		void Initialise();
		void Update();

		void RotateAboutY(float angle);
		void SetPosition(vec3 position);
		void SetRotation(quat rotation);
		void SetScale(vec3 scale);

		mat4x4  GetTransformation();

	public:
		static void Register(lua_State* L)
		{
			getGlobalNamespace(L)
				.beginNamespace("QEngine")
				.beginClass<Transform>("Transform")
				.addConstructor<void(*)()>()
				.addFunction("GetPosition", &Transform::GetPosition)
				.addFunction("SetPosition", &Transform::SetPosition)
				.addFunction("RotateAboutY", &Transform::RotateAboutY)
				.endClass()
				.endNamespace();
		}
	};
}
