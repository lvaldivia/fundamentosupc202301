#include "HLSLProgram.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "Error.h"

using namespace std;

HLSLProgram::HLSLProgram():programID(0),vertexShaderID(0),fragmentShaderID(0),numAtribute(0) {
}

HLSLProgram::~HLSLProgram() {
}


void HLSLProgram::addAtribute(const string attributeName) {
	glBindAttribLocation(programID, numAtribute++, attributeName.c_str());
}

void HLSLProgram::use() {
	glUseProgram(programID);
	for(int i = 0; i < numAtribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void HLSLProgram::unuse() {
	glUseProgram(0); 
	for (int i = 0; i < numAtribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void HLSLProgram::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath) {
	programID = glCreateProgram();
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0) {
		fatalError("Error creating Vertex Shader");
	}
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0) {
		fatalError("Error creating Fragment Shader");
	}
	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void HLSLProgram::compileShader(const string& shaderPath, GLuint id) {
	string filecontent = "";
	string line = "";
	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError(" Coul not open " + shaderPath);
	}
	while (getline(shaderFile,line)) {
		filecontent += line + "\n";
	}
	shaderFile.close();
	const char* contents = filecontent.c_str();
	glShaderSource(id, 1, &contents, nullptr);
	glCompileShader(id);
	GLint isCompiledd = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiledd);
	if (isCompiledd == GL_FALSE) {
		GLint maxLenght = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLenght);
		vector<GLchar> infoLog(maxLenght);
		glGetShaderInfoLog(id, maxLenght, &maxLenght, &infoLog[0]);
		fatalError("Shader could not compile " + printf("%s", &(infoLog[0])));
		glDeleteShader(id);
		return;
	}
}

void HLSLProgram::linkShader() {
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(programID);
		fatalError("Shaders could not link " + printf("%s", &(infoLog[0])));
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

GLuint HLSLProgram::getUniformLocation(const string& name)
{
	GLuint location = glGetUniformLocation(programID, name.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + name + " not found");
	}
	return location;
}


