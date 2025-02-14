#include "glew.h"

#include <string>

class ShaderVertex
{
public:
	std::string shaderFilePath;
	unsigned int shaderID = 0;


	ShaderVertex(std::string& t_shaderFilePath);
	~ShaderVertex();

	std::string parseShaderFile();
	void compileShader(std::string& shaderString);
};

class ShaderFragment
{
public:
	std::string shaderFilePath;
	unsigned int shaderID = 0;


	ShaderFragment(std::string& t_shaderFilePath);
	~ShaderFragment();

	std::string parseShaderFile();
	void compileShader(std::string& shaderString);
};