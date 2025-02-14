#include "Shader.h"

#include <fstream>
#include <sstream>

// VERTEX SHADER

ShaderVertex::ShaderVertex(std::string& t_shaderFilePath)
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

std::string ShaderVertex::parseShaderFile()
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

void ShaderVertex::compileShader(std::string& shaderString)
{
	shaderID = glCreateShader(GL_VERTEX_SHADER);
	const char* source = shaderString.c_str(); // const char because next call wont accept & or *
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);
}

// FRAGMENT SHADER

ShaderFragment::ShaderFragment(std::string& t_shaderFilePath)
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

std::string ShaderFragment::parseShaderFile()
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

void ShaderFragment::compileShader(std::string& shaderString)
{
	shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* source = shaderString.c_str(); // const char because next call wont accept & or *
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);
}
