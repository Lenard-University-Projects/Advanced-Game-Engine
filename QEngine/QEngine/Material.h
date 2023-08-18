#pragma once
#include "Shader.h"
#include "glut.h"
#include "glm.hpp"

using namespace std;
using namespace glm;

namespace QEngine
{
	struct MaterialInfo 
	{
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		GLfloat shininess;
	};

	// Materials are applied to the GameObject meshes during rendering.
	// They consist of a single shader and texture (only supports BMP textures).
	class Material 
	{
	public:
		Material(Shader * shader, const char * textureFileName, MaterialInfo  properties);
		~Material();

	private:
		MaterialInfo properties;
		Shader* shader;
		GLuint textureId;

		bool textureEnabled;

	public:
		// Pre-defined materials
		static MaterialInfo woodMaterial;
		static MaterialInfo whiteShineyMaterial;
		static MaterialInfo whiteMattMaterial;
		static MaterialInfo brassMaterial;
		static MaterialInfo redPlasticMaterial;

	public:
		void Apply();

		Shader * GetShader();
		MaterialInfo GetProperties();

		unsigned char* LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
	};
}
