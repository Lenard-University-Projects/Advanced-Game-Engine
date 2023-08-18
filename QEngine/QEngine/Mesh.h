#pragma once
#include <iostream>
#include "glew.h"
#include "glfw3.h"
#include "glm.hpp"
#include <vector>

using namespace std;

namespace QEngine
{
	class Mesh
	{
	public:
		Mesh() {}

		virtual ~Mesh(void)
		{
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}

	protected:
		GLuint vao;
		GLuint vbo;
		vector<GLfloat> vertices;
		vector<GLfloat> normals;
		vector<GLfloat> texcoords;

		int numberVertices;
	public:
		virtual void Initialise() = 0;
		virtual void Render() = 0;
	};
}
