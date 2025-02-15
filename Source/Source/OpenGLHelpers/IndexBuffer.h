#include "glew.h"

class IndexBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_Count;

public:
	IndexBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode);
	~IndexBuffer();

	void Bind() const ;
	void Unbind() const ;

	inline unsigned int GetCount() const { return m_Count; }
	void SetBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) ;
	void UpdateBufferSection(const void* data, unsigned int sizeInBytes, unsigned int offset) const ;
};