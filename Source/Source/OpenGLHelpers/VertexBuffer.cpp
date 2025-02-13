#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int& sizeInBytes, GLenum& GLBufferMode) //DOES NOT UNBIND BUFFER FOR THE GPU CALL SAVING, IT SHOULD BE EASY TO WORK WITH THIS THOUGH
{
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferData(m_rendererID, sizeInBytes, data, GLBufferMode);

}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetBuffer(const void* data, unsigned int& sizeInBytes, GLenum& GLBufferMode) const //DOES NOT UNBIND BUFFER
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferData(m_rendererID, sizeInBytes, data, GLBufferMode);
}

void VertexBuffer::UpdateBufferSection(const void* data, unsigned int& sizeInBytes, unsigned int& offset) const //DOES NOT UNBIND BUFFER
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferSubData(m_rendererID, offset, sizeInBytes, data);
}
