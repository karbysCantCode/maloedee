#include "Workspace.h"

#include <assert.h>

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
		m_Instances.emplace_back(ObjectInstance(m_ObjectChanged));
		newInstance = &m_Instances.back();
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
