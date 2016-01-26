#define GLEW_STATIC
#include <fstream>
#include <string>
#pragma comment(lib, "glew32s.lib")
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GraphicsMath.h"

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

bool ReadFile(const char* pFileName, std::string& outFile)
{
	std::ifstream f(pFileName);
	bool ret = false;

	if (f.is_open())
	{
		std::string line;
		while (std::getline(f, line))
		{
			outFile.append(line);
			outFile.append("\n");
		}
		f.close();
		ret = true;
	}
	else
	{
		fprintf(stderr, "Unable to open file '%s'\n", pFileName);
	}
	return ret;
}

static void AddShader(GLuint ShaderProgram, const char* ShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);
	if (ShaderObj == 0)
	{
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}
	const GLchar* ShaderSource[1];
	ShaderSource[0] = ShaderText;
	GLint lengths[1];
	lengths[0] = strlen(ShaderText);
	glShaderSource(ShaderObj, 1, ShaderSource, lengths);
	glCompileShader(ShaderObj);

	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, infoLog);
		fprintf(stderr, "Error compiling shader type: %d: '%s'", ShaderType, infoLog);
	}
	glAttachShader(ShaderProgram, ShaderObj);
}

static void RenderSceneCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

static void CompileShaders()
{
	GLuint ShaderProgram = glCreateProgram();
	if (ShaderProgram == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}
	std::string vs;
	std::string fs;
	// Read vertex shader from file system
	if (!ReadFile(pVSFileName, vs))
	{
		exit(1);
	}
	// Read fragment shader from file system
	if (!ReadFile(pFSFileName, fs))
	{
		exit(1);
	}
	// Compile vertex and fragment shaders and add to the shader
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(errorLog), NULL, errorLog);
		exit(1);
	}
	// Ensure shader program is valid, and confirm status
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(errorLog), NULL, errorLog);
		exit(1);
	}

	// Tell OpenGL to use this shader
	glUseProgram(ShaderProgram);
}

static void InitializeGlutCallback()
{
	glutDisplayFunc(RenderSceneCallback);
}

static void CreateVertexBuffers()
{
	Vector3f vertices[3];
	vertices[0] = Vector3f(-1.f, -1.f, 0.f);
	vertices[1] = Vector3f(1.f, -1.f, 0.f);
	vertices[2] = Vector3f(0.f, 1.f, 0.f);
	
	// sizeof gives the size of the Vector3f in bytes
	// Vector3f takes in 3 intergers which each interger is about 4 bytes each
	// 3 * 4 = 12 bytes, so to find the index of Vector3f, I have to divide by 12
	for (int i = 0; i < sizeof(vertices)/12; i++)
	{
		vertices[i] = vertices[i] * -1.f;
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Week 3");

	InitializeGlutCallback();

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.f, 0.f, 0.f, 0.f);

	CreateVertexBuffers();

	CompileShaders();

	glutMainLoop();
	return 0;
}