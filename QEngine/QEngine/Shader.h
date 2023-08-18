#pragma once
#include "glew.h"

namespace QEngine
{

	class Shader
	{
	public:
		Shader();
		Shader(const char * vertexShaderFileName, const char * fragmentShaderFileName);
		~Shader();

	private:
		GLuint program, v, f;

	public:
		void PrintShaderInfoLog(GLuint obj, const char * fragmentShaderFileName);
		void PrintProgramInfoLog(GLuint obj);
		char* ReadTextFile(const char *fileName);

		GLuint GetProgram();
	};

}