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
	uint32_t ObjectID; // dont change this you silly donkey

	struct VertexDataOrderPair
	{
		std::vector<float>& vertexData;
		std::vector<unsigned int>& vertexOrder;
	};

	struct Vertex
	{
		float Position[3];
		float Normals[3];
		uint32_t modelID;
	};
	static_assert(sizeof(long int) == sizeof(uint32_t));

	ObjectInstance(bool& workspaceChanged, bool& workspaceRecompile, uint32_t objectID);
	~ObjectInstance();

	void SetVertexData(const std::vector<Vertex>& vertexSet);
	void SetVertexOrderData(const std::vector<unsigned int>& vertexOrder);

	inline void SetColor(const glm::vec4& color) {  // MAY NOT BE GOOD IF CALLED ALOT
		m_color = color; 
		SSBOUpdate = true; 
		p_workspaceChanged = true; 
	};

	inline void SetPosition(const glm::vec3& position) { // MAY NOT BE GOOD IF CALLED ALOT
		m_Position = position;
		SSBOUpdate = true;
		p_workspaceChanged = true;
	};

	inline glm::vec4 GetColor() const { return m_color; }
	inline const glm::vec3& GetPosition() const { return m_Position; }

	VertexDataOrderPair GetObjectData();
};