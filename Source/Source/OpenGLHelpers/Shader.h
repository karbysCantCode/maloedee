#include "glew.h"
#include "HeaderLibraries/glm/glm.hpp"

#include <string>
#include <unordered_map>

class ShaderVertex
{
public:
	std::string shaderFilePath;
	unsigned int shaderID = 0;

	ShaderVertex(const std::string& t_shaderFilePath);
	~ShaderVertex();

	std::string parseShaderFile() const;
	void compileShader(std::string shaderString);
};

class ShaderFragment
{
public:
	std::string shaderFilePath;
	unsigned int shaderID = 0;


	ShaderFragment(const std::string& t_shaderFilePath);
	~ShaderFragment();

	std::string parseShaderFile() const;
	void compileShader(std::string shaderString);
};

class ShaderUniformHelper
{
private:
	std::unordered_map<std::string, int> m_UniformLocationCache;
	unsigned int m_BoundProgram = 0;
	int GetUniformLocation(const std::string& name);
public:
	void BindProgram(unsigned int programToBind);

	void SetUniform1f(const std::string& name, float v0);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};