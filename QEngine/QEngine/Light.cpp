#include "stdafx.h"
#include "Light.h"
#include "GameObject.h"

namespace QEngine{

	LightInfo Light::noonLight = {
		{ 0.00, 0.00, 0.00 },
		{ 1.00, 1.00, 1.00, 1.00 },
		{ 1.00, 1.00, 1.00, 1.00 },
		{ 1.00, 1.00, 1.00, 1.00 } 
	};

	LightInfo Light::duskLight = {
		{ 0.00, 0.00, 0.00 },
		{ 0.50, 0.50, 0.50, 1.00 },
		{ 0.50, 0.50, 0.50, 1.00 },
		{ 0.50, 0.50, 0.50, 1.00 } 
	};
	
	int Light::lightIndex = GL_LIGHT0;

	Light::Light(GameObject * gameObject, LightInfo info) : Component(gameObject)
	{
		index = lightIndex++;
		glEnable(index);
		properties = info;
	}

	Light::~Light(void) { }

	LightInfo Light::GetProperties()
	{
		properties.position = gameObject->GetTransform()->GetPosition();
		return properties;
	}
	void Light::Initialise() 
	{
		vec3 position = gameObject->GetTransform()->GetPosition();

		GLfloat light_pos[] = { position.x, position.y, position.z, 1.0 };
		glLightfv(index, GL_POSITION, light_pos);

		GLfloat ambient[] = { 0.2, 0.2, 0.2 };
		glLightfv(index, GL_AMBIENT, ambient);

		GLfloat specular[] = { 0.4, 0.4, 0.4 };
		glLightfv(index, GL_SPECULAR, specular);

		GLfloat diffuse[] = { 0.7, 0.7, 0.7 };
		glLightfv(index, GL_DIFFUSE, diffuse);
	}

	void Light::Update()
	{
		// Moved in the Initialise method so they are called only once and it seems
		// like it has the same effect on the game
	}
}