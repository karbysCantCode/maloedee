#include <vector>

#include "Instance.h"

#include "HeaderLibraries/glm/glm.hpp"

class ObjectInstance : public Instance // attach to instance so different types can be under the same vector
{
private:
	struct VertexPosition
	{
		float x, y, z;
	};

	std::vector<VertexPosition> m_vertexPositions;
	std::vector<unsigned int> m_vertexOrder;

	glm::vec4 m_color{ 1.0f,0.0f,1.0f,1.0f };

	bool& p_workspaceChanged;
public:
	const Instance::InstanceType Type;
	bool changed = false;

	ObjectInstance(bool& workspaceChanged);
	~ObjectInstance();

	void setVertexPositionData(const std::vector<VertexPosition>& vertexPositions);
	void setVertexOrderData(const std::vector<unsigned int>& vertexOrder);
	void setColor(const glm::vec4& color);

	float* getFloatArrayData();
};