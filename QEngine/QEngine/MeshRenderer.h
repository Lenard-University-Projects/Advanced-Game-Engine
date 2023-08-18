#pragma once
#include "renderer.h"
#include "Mesh.h"
#include <matrix_transform.hpp>
#include <transform.hpp>

using namespace glm;

namespace QEngine
{
	class MeshRenderer : public Renderer
	{
	public:
		MeshRenderer(GameObject* gameObject, Mesh* mesh, Material* shader);
		~MeshRenderer();

	private:
		GLuint matMVPIdx;
		GLuint matNIdx;
		GLuint matMVIdx;

		GLuint lAmbientIdx;
		GLuint lDiffuseIdx;
		GLuint lSpecularIdx;
		GLuint lPositionIdx;

		GLuint mAmbientIdx;
		GLuint mDiffuseIdx;
		GLuint mSpecularIdx;
		GLuint mShininessIdx;

		GLuint cameraPositionIdx;
		Mesh * mesh;

	public:
		void Update();
		void Initialise();
	};
}