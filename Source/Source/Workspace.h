#include "3DObject.h"

#include <memory>

class Workspace
{
private:
	std::vector<Instance> m_Instances;
	std::vector<float> m_VertexData;
	std::vector<unsigned int> m_VertexOrder;
	bool m_ObjectChanged = false;
public:

	Workspace();
	~Workspace();

	Instance* NewInstance(Instance::InstanceType instanceType);
	void Destroy(Instance* instance);
	
	void Render();
};