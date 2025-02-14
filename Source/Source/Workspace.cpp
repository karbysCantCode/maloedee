#include "Workspace.h"

#include <assert.h>
#include <algorithm> // for index buffer index offset

Workspace::Workspace()
{
}

Workspace::~Workspace()
{
}

Instance* Workspace::NewInstance(Instance::InstanceType instanceType)
{
	Instance* newInstance;

	switch (instanceType)
	{
	case Instance::OBJECT:
		ObjectInstance* newObject = new ObjectInstance(m_ObjectChanged);
		m_Instances.push_back(newObject);

		ObjectInstance::VertexDataOrderPair newObjectData = newObject->getObjectData();
		m_VertexData.resize(m_VertexData.size() + newObjectData.vertexData.size());
		m_VertexData.insert(m_VertexData.end(), newObjectData.vertexData.begin(), newObjectData.vertexData.end());

		const unsigned int VERTEX_ORDER_ARRAY_SIZE = m_VertexOrder.size();
		std::transform(newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end(), newObjectData.vertexOrder.begin(),
			[VERTEX_ORDER_ARRAY_SIZE](int x) { return x + VERTEX_ORDER_ARRAY_SIZE; });
		m_VertexOrder.insert(m_VertexOrder.end(), newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end());
		break;
	default:
		// INVALID INSTANCE TYPE SOMEHOW?? nah how do you do this
		// if you trigger this hit me up! i wanna know
		assert(false);
		break;
	}
	return newInstance;
}

void Workspace::Destroy(Instance* instance)
{

}

void Workspace::Render()
{

}
