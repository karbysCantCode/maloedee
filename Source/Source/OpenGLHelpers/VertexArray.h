#include "glew.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_rendererID;
public:
	inline VertexArray() { glGenVertexArrays(1, &m_rendererID); }
	inline ~VertexArray() { glDeleteVertexArrays(1, &m_rendererID); }

	void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)const;

	inline void Bind() const { glBindVertexArray(m_rendererID); }
	inline void Unbind() const { glBindVertexArray(0); }
};