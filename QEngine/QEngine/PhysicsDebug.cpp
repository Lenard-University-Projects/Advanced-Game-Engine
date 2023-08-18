#include "stdafx.h"
#include "PhysicsDebug.h"
#include "Graphics.h"
#include "Camera.h"


void PhysicsDebug::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color){
	if (m_debugMode){
		vertices.push_back(from.getX());
		vertices.push_back(from.getY());
		vertices.push_back(from.getZ());
		vertices.push_back(to.getX());
		vertices.push_back(to.getY());
		vertices.push_back(to.getZ());
	}
}

void PhysicsDebug::ToggleDebugFlag(int flag) {
	if (m_debugMode & flag)
		m_debugMode = m_debugMode & (~flag);
	else
		m_debugMode |= flag;
}

void PhysicsDebug::Initialise(){
	if (m_debugMode){
		debugShader = new QEngine::Shader("../Assets/Shaders/Debug.vert", "../Assets/Shaders/Debug.frag");
		matMVPIdx = glGetUniformLocation(debugShader->GetProgram(), "MVP");
	}
}

void PhysicsDebug::Draw(){
	if (m_debugMode){
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *  (vertices.size() + colours.size()), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, (sizeof(GLfloat) * vertices.size()), &vertices[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		numberVertices = vertices.size() / 2;
		vertices.clear();

		glUseProgram(debugShader->GetProgram());

		glm::mat4 mvp = QEngine::Graphics::GetProjectionMatrix() * QEngine::Graphics::GetMainCamera()->GetViewMatrix();

		glUniformMatrix4fv(matMVPIdx, 1, GL_FALSE, glm::value_ptr(mvp));

		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, numberVertices);
		glBindVertexArray(0);
	}
}