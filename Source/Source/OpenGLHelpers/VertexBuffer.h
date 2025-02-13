#include "glew.h"

class VertexBuffer
{
private:
	unsigned int m_rendererID;

public:
	VertexBuffer(const void* data, unsigned int& sizeInBytes, GLenum& GLBufferMode);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	 
	void SetBuffer(const void* data, unsigned int& sizeInBytes, GLenum& GLBufferMode) const;
	void UpdateBufferSection(const void* data, unsigned int& sizeInBytes, unsigned int& offset) const;
};