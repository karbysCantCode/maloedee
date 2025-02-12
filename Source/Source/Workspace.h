#include "3DObject.h"

#include <memory>

class Workspace
{
private:
	std::vector<Instance*> m_Instances;

public:
	bool ObjectChanged = false;

	Workspace();
	~Workspace();

	Instance* New(Instance::InstanceType instanceType);
	void Destroy(Instance* instance);
	
	void Render();
};