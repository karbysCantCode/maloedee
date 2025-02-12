#include "3DObject.h"

ObjectInstance::ObjectInstance(bool& workspaceChanged)
	: Type(InstanceType::OBJECT)
	, p_workspaceChanged(workspaceChanged)
{

}

ObjectInstance::~ObjectInstance()
{
}

void ObjectInstance::setVertexPositionData(const std::vector<VertexPosition>& vertexPositions) // this wont work vertex potisiot is private
{
	m_vertexPositions = vertexPositions;
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

float* ObjectInstance::getFloatArrayData()
{

	return nullptr;
}
