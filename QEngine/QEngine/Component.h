#pragma once
#include "Object.h"
#include "glm.hpp"
#include "matrix_transform.hpp"

namespace QEngine
{
	class Component:public Object 
	{
	public:
		Component();
		~Component();
		Component(class GameObject * gameObject);

	public:
		Component* next;
		class GameObject* gameObject;

	public:
		virtual void Initialise() = 0;
		virtual void Update() = 0;
	};
}