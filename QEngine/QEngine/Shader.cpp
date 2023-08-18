#include "stdafx.h"
#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace QEngine
{
	Shader::Shader() { }

	Shader::Shader(const char * vertexShaderFileName, const char * fragmentShaderFileName)
	{
		char *vs = NULL, *fs = NULL;

		v = glCreateShader(GL_VERTEX_SHADER);
		f = glCreateShader(GL_FRAGMENT_SHADER);

		vs = ReadTextFile(vertexShaderFileName);
		fs = ReadTextFile(fragmentShaderFileName);

		const char* vv = vs;
		const char* ff = fs;

		glShaderSource(v, 1, &vv, NULL);
		glShaderSource(f, 1, &ff, NULL);

		free(vs); 
		free(fs);

		glCompileShader(v);
		glCompileShader(f);

		PrintShaderInfoLog(v, vertexShaderFileName);
		PrintShaderInfoLog(f, fragmentShaderFileName);

		program = glCreateProgram();
		glAttachShader(program, v);
		glAttachShader(program, f);
		glLinkProgram(program);

		PrintProgramInfoLog(program);
		glUseProgram(program);
	}

	Shader::~Shader() { }

	void Shader::PrintShaderInfoLog(GLuint obj, const char * shaderFileName)
	{
		GLint compiled;

		glGetShaderiv(obj, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			int infologLength = 0;
			int charsWritten  = 0;
			char *infoLog;

			glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

			if (infologLength > 0)
			{
				infoLog = (char *)malloc(infologLength);
				glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);

				printf("FAILED... %s\n", infoLog);

				free(infoLog);
			}
		}
		else
			printf("PASS... Shader %s compiled successfully \n", shaderFileName);
	}

	void Shader::PrintProgramInfoLog(GLuint obj)
	{
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);

			printf("%s\n", infoLog);

			free(infoLog);
		}
	}

	char *Shader::ReadTextFile(const char *fileName) 
	{
		FILE* fp;
		char* content	= NULL;
		int count		= 0;

		if (fileName != NULL) 
		{
			errno_t err = fopen_s(&fp,fileName, "rt");

			if (err != NULL) 
				fprintf(stderr, "Cannot open config file %s!\n", fileName);
			else 
			{
				fseek(fp, 0, SEEK_END);
				count = ftell(fp);

				rewind(fp);

				if (count > 0) 
				{
					content = (char *)malloc(sizeof(char) * (count + 1));
					count	= fread(content, sizeof(char), count, fp);

					content[count] = '\0';
				}

				fclose(fp);
			}
		}
		return content;
	}

	GLuint Shader::GetProgram()
	{
		return program;
	}
}