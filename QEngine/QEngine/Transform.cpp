#include "stdafx.h"
#include "Transform.h"
#include "GameObject.h"

namespace QEngine
{
	vec3 const Transform::FORWARD(0.0, 0.0, 1.0);
	vec3 const Transform::UP(0.0, 1.0, 0.0);
	vec3 const Transform::RIGHT(1.0, 0.0, 0.0);

	Transform::Transform()
	{
		position = vec3(0.0, 0.0, 0.0);
		rotation = quat(vec3(0.0, 0.0, 0.0));
		scale = vec3(0.0, 0.0, 0.0);
	}

	Transform::Transform(GameObject * gameObject, vec3 position, vec3 rotation, vec3 scale) :Component(gameObject)
	{
		//--
		this->position = position;

		// Converting euler arguments into quaternion
		float x = radians(rotation.x);
		float y = radians(rotation.y);
		float z = radians(rotation.z);

		this->rotation = quat(vec3(x, y, z));

		//--
		this->scale = scale;
	}

	Transform::~Transform() { }

	vec3 Transform::GetPosition()
	{
		return position;
	}

	quat Transform::GetRotation()
	{
		return rotation;
	}

	vec3 Transform::GetScale()
	{
		return scale;
	}

	void Transform::Initialise() { }

	void Transform::Update() { }

	void Transform::RotateAboutY(float angle)
	{
		quat temp = angleAxis(angle, vec3(0.0, 1.0, 0.0));
		rotation = temp * rotation;
	}

	void Transform::SetPosition(vec3 position)
	{
		this->position = position;
	}

	void Transform::SetRotation(quat rotation)
	{
		this->rotation = rotation;
	}

	void Transform::SetScale(vec3 scale)
	{
		this->scale = scale;
	}

	mat4x4 Transform::GetTransformation()
	{
		// Had to use glm because we already have scale defined and it was conflicting
		mat4x4 scaleMatrix			= glm::scale(mat4x4(1.0f), scale);
		mat4x4 rotationMatrix		= mat4_cast(rotation);
		mat4x4 translationMatrix	= translate(mat4x4(1), position);

		return translationMatrix * rotationMatrix * scaleMatrix;
	}
}
