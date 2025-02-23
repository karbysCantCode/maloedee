#include "3DObject.h"

#include "IndexBuffer.h"
#include "VertexArray.h" // VB and VBL included in VAO :D

#include "Shader.h"
#include "ShaderStorageBuffer.h"

#include "HeaderLibraries/glm/gtc/matrix_transform.hpp"

#include <memory>
#include <typeinfo>

#include <assert.h>
#include <algorithm> // for index buffer index offset
#include <unordered_map>

class RenderGroup
{
private:
	float m_ScreenWidth;
	float m_ScreenHeight;

	std::vector<Instance*> m_3DInstances;
	std::vector<float> m_VertexData;
	std::unordered_map<uint32_t, unsigned int> m_ObjectIDFirstDataEntry;
	std::vector<unsigned int> m_VertexOrder;
	std::unordered_map<uint32_t, unsigned int> m_ObjectIDFirstOrderEntry;
	std::vector<float> m_SSBOData;
	unsigned int m_NextFree3DObjectID = 0;
	bool m_ObjectChanged = false;
	bool m_RecompileObjectData = false;

	IndexBuffer* m_IndexBuffer = nullptr;
	VertexBuffer* m_VertexBuffer = nullptr;
	VertexArray m_VertexArray;

	unsigned int m_Program;
	ShaderFragment m_FragmentShader;
	ShaderVertex m_VertexShader;
	ShaderUniformHelper m_UniformHelper;
	ShaderStorageBuffer* m_ShaderStorageBuffer = nullptr;

	glm::mat4 m_Projection;

	void Recompile3DInstanceData();
	void RecompileProgram();
public:
	//call UpdateVertexArray() once done changing this!
	VertexBufferLayout vertexBufferLayout;

	RenderGroup(const float ScreenWidth, const float ScreenHeight, const float FOV);
	~RenderGroup();

	//call after updating vertexbufferlayout
	void UpdateVertexArray(); 

	Instance* NewInstance(Instance::InstanceType instanceType);
	void Destroy(Instance* instance);

	void Update();
	void Render();
};