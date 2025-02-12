#include <vector>

#include "Instance.h"

#include "HeaderLibraries/glm/glm.hpp"

class ObjectInstance : public Instance // attach to instance so different types can be under the same vector
{
private:
	std::vector<float> m_vertexPositions;
	std::vector<unsigned int> m_vertexOrder;

	glm::vec4 m_color;

public:
	const Instance::InstanceType Type;

	ObjectInstance();
	~ObjectInstance();


};