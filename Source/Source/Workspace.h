#include "3DObject.h"

#include <memory>

class Workspace
{
private:
	std::vector<Instance*> m_Instances;
	bool m_ObjectChanged = false;
public:

	Workspace();
	~Workspace();

	Instance* NewInstance(Instance::InstanceType instanceType);
	void Destroy(Instance* instance);
	
	void Render();
};