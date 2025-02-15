#include "glew.h"

class VertexBuffer
{
private:
	unsigned int m_rendererID;

public:
	VertexBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode);
	inline ~VertexBuffer() { glDeleteBuffers(1, &m_rendererID); }

	inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); }
	inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	 
	void SetBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) const;
	void UpdateBufferSection(const void* data, unsigned int sizeInBytes, unsigned int offset) const;
};