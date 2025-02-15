#include "glew.h"

class IndexBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_Count;

public:
	IndexBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode);
	~IndexBuffer();

	inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); }
	inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	inline unsigned int GetCount() const { return m_Count; }
	void SetBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) ;
	void UpdateBufferSection(const void* data, unsigned int sizeInBytes, unsigned int offset) const ;
};