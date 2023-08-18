#include "stdafx.h"
#include "Object.h"

namespace QEngine
{
	int Object::instances = 0;

	Object::Object()
	{
		instances++;
		this->id = instances;
	}

	Object::~Object() { }

	int Object::GetID()
	{
		return id;
	}
}