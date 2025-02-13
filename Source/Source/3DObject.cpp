#include "3DObject.h"

#include <memory>

ObjectInstance::ObjectInstance(bool& workspaceChanged)
	: Type(InstanceType::OBJECT)
	, p_workspaceChanged(workspaceChanged)
{

}

ObjectInstance::~ObjectInstance()
{
	p_workspaceChanged = true;
}

void ObjectInstance::setVertexPositionData(const std::vector<float>& vertexPositions) // this will work :)
{
	const unsigned int FLOATS_IN_POSITION = 3;
	const unsigned int FLOATS_IN_COLOR = 4;
	const unsigned int FLOATS_IN_VERTEX = FLOATS_IN_COLOR + FLOATS_IN_POSITION;
	const size_t VERTICES_IN_DATA = vertexPositions.size() / 3;

	m_vertexData.resize(FLOATS_IN_VERTEX * VERTICES_IN_DATA);

	for (size_t Index = 0; Index < VERTICES_IN_DATA; Index++)
	{
		const float newData[FLOATS_IN_VERTEX] =
		{
			vertexPositions[Index],vertexPositions[Index+1],vertexPositions[Index+2],
			m_color[0], m_color[1], m_color[2], m_color[3]
		};


		std::memcpy(&m_vertexData[Index * FLOATS_IN_VERTEX], &newData, FLOATS_IN_VERTEX * sizeof(float));
	}

	p_workspaceChanged = true;
	changed = true;
}

void ObjectInstance::setVertexOrderData(const std::vector<unsigned int>& vertexOrder)
{
	m_vertexOrder = vertexOrder;
	p_workspaceChanged = true;
	changed = true;
}

void ObjectInstance::setColor(const glm::vec4& color)
{
	m_color = color;
	p_workspaceChanged = true;
	changed = true;
}

float* ObjectInstance::getObjectDataAsFloatArray(unsigned int& size)
{
	size = static_cast<unsigned int>(m_vertexData.size()); // silence c4267 warning by casting

	return &m_vertexData[0];
}
