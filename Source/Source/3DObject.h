#include <vector>

#include "Instance.h"

#include "HeaderLibraries/glm/glm.hpp"

class ObjectInstance : public Instance // attach to instance so different types can be under the same vector
{
private:

	std::vector<float> m_vertexData;
	std::vector<unsigned int> m_vertexOrder;

	glm::vec4 m_color{ 1.0f,0.0f,1.0f,1.0f };

	bool& p_workspaceChanged;
public:
	const Instance::InstanceType Type;
	bool changed = true;

	struct VertexDataOrderPair
	{
		std::vector<float>& vertexData;
		std::vector<unsigned int>& vertexOrder;
	};

	ObjectInstance(bool& workspaceChanged);
	~ObjectInstance();

	void setVertexPositionData(const std::vector<float>& vertexPositions);
	void setVertexOrderData(const std::vector<unsigned int>& vertexOrder);
	void setColor(const glm::vec4& color);

	VertexDataOrderPair getObjectData();
};