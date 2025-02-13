#include "glew.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_rendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)const;

	void Bind() const;
	void Unbind() const;
};