#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

// VERTEX SHADER

ShaderVertex::ShaderVertex(const std::string& t_shaderFilePath)
	: shaderFilePath(t_shaderFilePath)
{
	if (!shaderFilePath.empty())
	{
		compileShader(parseShaderFile());
	}
}

ShaderVertex::~ShaderVertex()
{
	glDeleteShader(shaderID);
}

std::string ShaderVertex::parseShaderFile() const 
{
	std::ifstream file(shaderFilePath);
	std::string line;
	std::stringstream ss;

	while (std::getline(file, line))
	{
		ss << line << std::endl;
	}

	return ss.str();
}

void ShaderVertex::compileShader(std::string shaderString)
{
	shaderID = glCreateShader(GL_VERTEX_SHADER);
	const char* source = shaderString.c_str(); // const char because next call wont accept & or *
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	GLint vertex_compiled;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(shaderID, 1024, &log_length, message);
		std::cout << message << std::endl;
		// Write the error to a log
	}
}

// FRAGMENT SHADER

ShaderFragment::ShaderFragment(const std::string& t_shaderFilePath)
	: shaderFilePath(t_shaderFilePath)
{
	if (!shaderFilePath.empty())
	{
		compileShader(parseShaderFile());
	}
}

ShaderFragment::~ShaderFragment()
{
	glDeleteShader(shaderID);
}

std::string ShaderFragment::parseShaderFile() const 
{
	std::ifstream file(shaderFilePath);
	std::string line;
	std::stringstream ss;

	while (std::getline(file, line))
	{
		ss << line << std::endl;
	}

	return ss.str();
}

void ShaderFragment::compileShader(std::string shaderString)
{
	shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* source = shaderString.c_str(); // const char because next call wont accept & or *
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	GLint fragment_compiled;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(shaderID, 1024, &log_length, message);
		std::cout << message << std::endl;
		// Write the error to a log
	}
}

// SHADER UNIFORM HELPER

int ShaderUniformHelper::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	const int uniformLocation = glGetUniformLocation(m_BoundProgram, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "SHADER WARNING: UNIFORM \"" << name << "\" DOES NOT EXIST!" << std::endl;
	}
	m_UniformLocationCache[name] = uniformLocation;
	return uniformLocation;
}

void ShaderUniformHelper::BindProgram(unsigned int programToBind)
{
	m_BoundProgram = programToBind;
}

void ShaderUniformHelper::SetUniform1f(const std::string& name, float v0)
{
	glUniform1f(GetUniformLocation(name), v0);
}

void ShaderUniformHelper::SetUniform2f(const std::string& name, float v0, float v1)
{
	glUniform2f(GetUniformLocation(name), v0, v1);
}

void ShaderUniformHelper::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void ShaderUniformHelper::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void ShaderUniformHelper::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}
