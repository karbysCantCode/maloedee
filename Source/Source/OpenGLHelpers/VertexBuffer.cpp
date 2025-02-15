#include "VertexBuffer.h"

#include "BugHuntingKit.h" // debug

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) //DOES NOT UNBIND BUFFER FOR THE GPU CALL SAVING, IT SHOULD BE EASY TO WORK WITH THIS THOUGH
{
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GLBufferMode);

}

void VertexBuffer::SetBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) const //DOES NOT UNBIND BUFFER
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GLBufferMode);
	GLAssertError();
}

void VertexBuffer::UpdateBufferSection(const void* data, unsigned int sizeInBytes, unsigned int offset) const //DOES NOT UNBIND BUFFER
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeInBytes, data);
}
