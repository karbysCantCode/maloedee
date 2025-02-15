#include "3DObject.h"

#include <memory>
#include <cstdint>
#include <bit>

ObjectInstance::ObjectInstance(bool& workspaceChanged, bool& workspaceRecompile, uint32_t objectID)
	: p_workspaceChanged(workspaceChanged)
	, p_workspaceRecompile(workspaceRecompile)
	, ObjectID(objectID)
{
	Type = Instance::InstanceType::OBJECT;
}

ObjectInstance::~ObjectInstance()
{
	p_workspaceChanged = true;
}

void ObjectInstance::SetVertexPositionData(const std::vector<float>& vertexPositions) // this will work :)
{

	constexpr unsigned int FLOATS_IN_POSITION = 3;
	//constexpr unsigned int FLOATS_IN_COLOR = 4;
	constexpr unsigned int UINT32_IN_MODEL_ID = 1;
	constexpr unsigned int FLOATS_IN_VERTEX = FLOATS_IN_POSITION + UINT32_IN_MODEL_ID;
	constexpr unsigned int UINT32_IN_VERTEX = UINT32_IN_MODEL_ID;
	const size_t VERTICES_IN_DATA = vertexPositions.size() / FLOATS_IN_POSITION;

	if (VERTICES_IN_DATA != m_vertexData.size()) { p_workspaceRecompile = true; }

	m_vertexData.resize(FLOATS_IN_VERTEX * VERTICES_IN_DATA);

	for (size_t Index = 0; Index < VERTICES_IN_DATA; Index++)
	{
		const unsigned int INDEX_MUL_FIP = Index * FLOATS_IN_POSITION;
		const float newData[FLOATS_IN_VERTEX] =
		{
			vertexPositions[INDEX_MUL_FIP],
			vertexPositions[INDEX_MUL_FIP + 1],
			vertexPositions[INDEX_MUL_FIP + 2],

			//m_color[0], 
			//m_color[1], 
			//m_color[2], 
			//m_color[3],

			std::_Bit_cast<float>(ObjectID) // so uint32 will exist in a float array -  does NOT change the value, simply casts the type to a float, doesnt change bit data
		};


		std::memcpy(&m_vertexData[Index * FLOATS_IN_VERTEX], &newData, FLOATS_IN_VERTEX * sizeof(float));
	}

	p_workspaceChanged = true;
	Changed = true;
}

void ObjectInstance::SetVertexOrderData(const std::vector<unsigned int>& vertexOrder)
{
	if (vertexOrder.size() != m_vertexOrder.size()) { p_workspaceRecompile = true; }
	m_vertexOrder = vertexOrder;
	p_workspaceChanged = true;
	Changed = true;
}

//void ObjectInstance::SetColor(const glm::vec4& color)
//{
//	m_color = color;
//	constexpr unsigned int FLOATS_IN_COLOR = 4;
//	constexpr unsigned int FLOATS_IN_POSITION = 3;
//	constexpr unsigned int UINT32_IN_MODEL_ID = 1;
//	constexpr unsigned int FLOATS_IN_VERTEX = FLOATS_IN_COLOR + FLOATS_IN_POSITION + UINT32_IN_MODEL_ID;
//	const unsigned int VERTICES_IN_DATA = m_vertexData.size() / FLOATS_IN_VERTEX;
//	for (size_t Index = 0; Index < VERTICES_IN_DATA; Index++)
//	{
//		std::memcpy(&m_vertexData[Index * FLOATS_IN_VERTEX + FLOATS_IN_POSITION], &m_color, FLOATS_IN_COLOR * sizeof(float));
//	}
//	p_workspaceChanged = true;
//	Changed = true;
//}

//void ObjectInstance::SetPosition(const glm::vec3& postion)
//{
//	SSBOUpdate = true;
//	p_workspaceChanged = true;
//	m_Position = postion;
//}

ObjectInstance::VertexDataOrderPair ObjectInstance::GetObjectData()
{
	return { m_vertexData, m_vertexOrder };
}
