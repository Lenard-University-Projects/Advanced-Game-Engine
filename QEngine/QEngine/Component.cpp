#include "stdafx.h"
#include "Component.h"

namespace QEngine
{
	Component::Component() { }

	Component::Component(GameObject* gameObject)
	{
		this->gameObject = gameObject;
		next = 0;
	}

	Component::~Component(){ }
}