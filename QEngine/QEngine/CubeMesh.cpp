#include "stdafx.h"
#include "CubeMesh.h"

namespace QEngine{

	GLfloat CubeMesh::cubeTriangles[] = {
		1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0,			// Front
		-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0,			// Front
		1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0,			// Right
		1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0,		// Right
		-1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0,		// Back
		1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0,		// Back
		-1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0,		// Left
		-1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0,		// Left
		-1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,			// Top
		1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0,			// Top
		1.0, -1.0, -1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0,		// Bottom
		-1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0		// Bottom
	};	


	GLfloat CubeMesh::cubeNormals[] = {
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
		0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
		-1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
		0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
		0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0 
	};

	GLfloat CubeMesh::cubeTexture[] = {
		1.0, 1.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
		1.0, 1.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
		1.0, 1.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
		1.0, 1.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
		1.0, 1.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
		1.0, 1.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	};

	CubeMesh::CubeMesh() { }

	CubeMesh::~CubeMesh() { }

	void CubeMesh::Initialise()
	{
		// Insert the array data into vertices, normals, and texture coordinates 
		vertices.insert(	vertices.begin(),	&cubeTriangles[0],	&cubeTriangles[108]);
		normals.insert(		normals.begin(),	&cubeNormals[0],	&cubeNormals[108]);
		texcoords.insert(	texcoords.begin(),	&cubeTexture[0],	&cubeTexture[84]);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Create vertex buffer 
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER,		sizeof(GLfloat) * (vertices.size() + normals.size() + texcoords.size()), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER,	sizeof(GLfloat) * vertices.size(), sizeof(GLfloat) * normals.size(), &normals[0]);
		glBufferSubData(GL_ARRAY_BUFFER,	sizeof(GLfloat) * (vertices.size() + normals.size()), sizeof(GLfloat) * texcoords.size(), &texcoords[0]);
			
		// Specifies the location of the data within the buffer. 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)(sizeof(GLfloat) * (vertices.size())));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)(sizeof(GLfloat) * (vertices.size() + normals.size())));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		numberVertices = vertices.size() / 3;
		vertices.clear();
		normals.clear();
		texcoords.clear();
	}

	void CubeMesh::Render()
	{
		glBindVertexArray(vao);

		// Element cube exercise
		glDrawArrays(GL_TRIANGLES, 0, numberVertices);

		// Unbind the vertex array
		glBindVertexArray(0);
	}
}