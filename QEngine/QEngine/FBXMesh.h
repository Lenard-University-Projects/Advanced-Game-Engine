#pragma once
#include "Mesh.h"
#include "SceneContext.h"
#include "renderer.h"
#include "Shader.h"

namespace QEngine 
{
	class FBXMesh : public Mesh
	{
	public:
		FBXMesh(const char* fileName);
		~FBXMesh();

	private:
		const char* fileName;

	private:
		void GetFBXInfo(FbxNode* node);

	public:
		void Initialise();
		void Render();
	};
}
