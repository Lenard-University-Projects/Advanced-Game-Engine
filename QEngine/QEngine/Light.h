#pragma once
#include "Component.h"
#include "glew.h"

using namespace glm;

namespace QEngine{

	struct LightInfo{
		vec3 position;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
	};

	class Light : public Component
	{
	public:
		Light(GameObject* gameObject, LightInfo info);
		~Light();

	public:
		static LightInfo duskLight;
		static LightInfo noonLight;
		static LightInfo green;
		static int lightIndex;

	private:
		GLenum index;
		LightInfo properties;

	public:
		void Initialise();
		void Update();

		LightInfo GetProperties();
	};
}