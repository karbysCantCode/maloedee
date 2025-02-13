#include "glew.h"

class IndexBuffer
{
private:
	unsigned int m_rendererID;

public:
	IndexBuffer(const void* data, unsigned int& sizeInBytes, GLenum& GLBufferMode);
	~IndexBuffer();

	void Bind() const ;
	void Unbind() const ;

	void SetBuffer(const void* data, unsigned int& sizeInBytes, GLenum& GLBufferMode) const ;
	void UpdateBufferSection(const void* data, unsigned int& sizeInBytes, unsigned int& offset) const ;
};