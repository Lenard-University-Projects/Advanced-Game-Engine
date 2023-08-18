#pragma once
#include "..\libraries\bullet3-2.87\src\LinearMath\btIDebugDraw.h"
#include <vector>
#include "glm.hpp"
#include "type_ptr.hpp"
#include "Shader.h"


using namespace std;

class PhysicsDebug : public btIDebugDraw{
private:
	GLuint vao;
	GLuint vbo;
	vector<GLfloat> vertices;
	vector<GLfloat> colours;
	int numberVertices;
	QEngine::Shader *debugShader;
	GLuint matMVPIdx;
public:
	void Initialise();
	virtual void setDebugMode(int debugMode) override { m_debugMode = debugMode; }
	virtual int getDebugMode() const override { return m_debugMode; }
	virtual void  drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) override{}
	virtual void  drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override;
	virtual void  reportErrorWarning(const char* warningString) override {}
	virtual void  draw3dText(const btVector3 &location, const char* textString) override {}
	void ToggleDebugFlag(int flag);
	void Draw();
protected:
	int m_debugMode;
};
