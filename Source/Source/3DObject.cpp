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

void ObjectInstance::SetVertexData(const std::vector<Vertex>& vertexSet) // this will work :)
{
	const unsigned int VERTICES_IN_DATA = vertexSet.size();
	constexpr unsigned int FLOATS_IN_VERTEX = sizeof(Vertex) / sizeof(float);

	if (VERTICES_IN_DATA != m_vertexData.size()) { p_workspaceRecompile = true; }

	m_vertexData.resize(FLOATS_IN_VERTEX * VERTICES_IN_DATA);

	for (unsigned int Index = 0; Index < VERTICES_IN_DATA; Index++)
	{
		const unsigned int INDEX_OFFSET = Index * FLOATS_IN_VERTEX;
		const float newData[FLOATS_IN_VERTEX] =
		{
			vertexSet[Index].Position[0],
			vertexSet[Index].Position[1],
			vertexSet[Index].Position[2],

			vertexSet[Index].Normals[0],
			vertexSet[Index].Normals[1],
			vertexSet[Index].Normals[2],

			std::_Bit_cast<float>(ObjectID) // so uint32 will exist in a float array -  does NOT change the value, simply casts the type to a float, doesnt change bit data
		};


		std::memcpy(&m_vertexData[INDEX_OFFSET], &newData, sizeof(Vertex));
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

ObjectInstance::VertexDataOrderPair ObjectInstance::GetObjectData()
{
	return { m_vertexData, m_vertexOrder };
}
