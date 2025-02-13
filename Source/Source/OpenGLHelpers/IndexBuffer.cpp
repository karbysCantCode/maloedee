#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int& countOfIndicies, GLenum& GLBufferMode)
{
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, countOfIndicies * sizeof(unsigned int), data, GLBufferMode);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetBuffer(const void* data, unsigned int& countOfIndicies, GLenum& GLBufferMode) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, countOfIndicies * sizeof(unsigned int), data, GLBufferMode);
}

void IndexBuffer::UpdateBufferSection(const void* data, unsigned int& countOfIndicies, unsigned int& offset) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, countOfIndicies * sizeof(unsigned int), data );
}
