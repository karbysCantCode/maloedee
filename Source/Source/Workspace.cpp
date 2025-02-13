#include "Workspace.h"

Workspace::Workspace()
{
}

Workspace::~Workspace()
{
}

Instance* Workspace::NewInstance(Instance::InstanceType instanceType)
{
	switch (instanceType)
	{
	case Instance::OBJECT:
		Instance* newInstance = new ObjectInstance(m_ObjectChanged);
		break;
	default:
		break;
	}
	return nullptr;
}

void Workspace::Destroy(Instance* instance)
{

}

void Workspace::Render()
{

}
