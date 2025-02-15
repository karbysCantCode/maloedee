#include "3DObject.h"

#include "IndexBuffer.h"
#include "VertexArray.h" // VB and VBL included in VAO :D

#include "Shader.h"
#include "ShaderStorageBuffer.h"

#include "HeaderLibraries/glm/gtc/matrix_transform.hpp"

#include <memory>

#include "BugHuntingKit.h" // debug

class Workspace
{
private:
	float m_ScreenWidth;
	float m_ScreenHeight;

	std::vector<Instance*> m_3DInstances;
	std::vector<float> m_VertexData;
	std::unordered_map<uint32_t, unsigned int> m_ObjectIDFirstDataEntry;
	std::vector<unsigned int> m_VertexOrder;
	std::unordered_map<uint32_t, unsigned int> m_ObjectIDFirstOrderEntry;
	std::vector<glm::vec3> m_ObjectPositions;
	bool m_ObjectChanged = false;
	bool m_RecompileObjectData = false;

	IndexBuffer* m_IndexBuffer = nullptr;
	VertexBuffer* m_VertexBuffer = nullptr;
	VertexArray m_VertexArray;
	VertexBufferLayout m_VertexBufferLayout;

	unsigned int m_Program;
	ShaderFragment m_FragmentShader;
	ShaderVertex m_VertexShader;
	ShaderUniformHelper m_UniformHelper;
	ShaderStorageBuffer* m_ShaderStorageBuffer = nullptr;

	glm::mat4 m_Projection;

	void Recompile3DInstanceData();
public:

	Workspace(const float ScreenWidth, const float ScreenHeight);
	~Workspace();

	Instance* NewInstance(Instance::InstanceType instanceType);
	void Destroy(Instance* instance);
	
	void Update();
	void Render();
};