#include <vector>

#include "Instance.h"

#include "HeaderLibraries/glm/glm.hpp"

class ObjectInstance : public Instance // attach to instance so different types can be under the same vector
{
private:

	std::vector<float> m_vertexData;
	std::vector<unsigned int> m_vertexOrder;

	glm::vec4 m_color{ 1.0f,0.0f,1.0f,1.0f };
	glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };

	bool& p_workspaceChanged;
	bool& p_workspaceRecompile;
public:
	uint32_t ObjectID = 0; // dont change this you silly donkey

	struct VertexDataOrderPair
	{
		std::vector<float>& vertexData;
		std::vector<unsigned int>& vertexOrder;
	};

	ObjectInstance(bool& workspaceChanged, bool& workspaceRecompile);
	~ObjectInstance();

	void SetVertexPositionData(const std::vector<float>& vertexPositions);
	void SetVertexOrderData(const std::vector<unsigned int>& vertexOrder);
	void SetColor(const glm::vec4& color);
	void SetPosition(const glm::vec3& postion);

	inline glm::vec4 GetColor() const { return m_color; }
	inline const glm::vec3& GetPosition() const { return m_Position; }

	VertexDataOrderPair GetObjectData();
};