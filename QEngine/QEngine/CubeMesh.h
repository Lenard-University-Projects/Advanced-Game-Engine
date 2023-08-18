#pragma once
#include "Mesh.h"

namespace QEngine
{
	class CubeMesh : public Mesh
	{
	public:
		CubeMesh();
		~CubeMesh();

	private:
		static GLfloat cubeTriangles[];
		static GLfloat cubeTexture[];
		static GLfloat cubeNormals[];

	public:
		void Initialise();
		void Render();
	};
}
