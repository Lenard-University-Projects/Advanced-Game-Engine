#include "stdafx.h"
#include "SphereMesh.h"
using namespace std;

namespace QEngine{

	SphereMesh::SphereMesh() { }

	SphereMesh::~SphereMesh(){
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	void SphereMesh::Create(double r, int divisions, int trash){
		double x, y, z, dTheta = 180 / divisions, dLon = 360 / divisions, degToRad = 3.141592665885 / 180;
		double u, v;
		for (double lat = 0; lat <= 180; lat += dTheta){
			for (double lon = 0; lon <= 360; lon += dLon){
				//Vertex 1
				x = r*cos(lon * degToRad) * sin(lat * degToRad);
				y = r*sin(lon * degToRad) * sin(lat * degToRad);
				z = r*cos(lat * degToRad);
				u = lon / 360 - 0.25;
				v = lat / 180;
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
				texcoords.push_back(u);
				texcoords.push_back(v);

				//Vetex 2
				x = r*cos(lon * degToRad) * sin((lat + dTheta)* degToRad);
				y = r*sin(lon * degToRad) * sin((lat + dTheta) * degToRad);
				z = r*cos((lat + dTheta) * degToRad);
				u = lon / 360 - 0.25;
				v = (lat + dTheta - 1) / (180);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
				texcoords.push_back(u);
				texcoords.push_back(v);

				//Vertex 3
				x = r*cos((lon + dLon) * degToRad) * sin((lat)* degToRad);
				y = r*sin((lon + dLon) * degToRad) * sin((lat)* degToRad);
				z = r*cos((lat)* degToRad);
				u = (lon + dLon) / (360) - 0.25;
				v = (lat) / 180;
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
				texcoords.push_back(u);
				texcoords.push_back(v);

				//Vertex 4
				x = r*cos((lon + dLon) * degToRad) * sin((lat + dTheta)* degToRad);
				y = r*sin((lon + dLon)* degToRad) * sin((lat + dTheta)* degToRad);
				z = r*cos((lat + dTheta)* degToRad);
				u = (lon + dLon) / 360 - 0.25;
				v = (lat + dTheta) / (180);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
				texcoords.push_back(u);
				texcoords.push_back(v);
			}
		}
	}

	void SphereMesh::Initialise(){
		Create(1.0, 30, 30 );
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		// Create vertex buffer 
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *  (vertices.size() + normals.size() + texcoords.size()), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, (sizeof(GLfloat) * vertices.size()), &vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), sizeof(GLfloat) * normals.size(), &normals[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (vertices.size() + normals.size()), sizeof(GLfloat) * texcoords.size(), &texcoords[0]);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)(sizeof(GLfloat) * vertices.size()));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)((sizeof(GLfloat) * (vertices.size() + normals.size()))));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		numberVertices = vertices.size() / 3;
		vertices.clear();
		texcoords.clear();
		normals.clear();
	}

	void SphereMesh::Render(){
		glBindVertexArray(vao);
		// Element cube exercise
		glDrawArrays(GL_QUAD_STRIP, 0, numberVertices);
		// Unbind the vertex array
		glBindVertexArray(0);
	}
}