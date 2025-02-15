#include "ShaderStorageBuffer.h"

ShaderStorageBuffer::ShaderStorageBuffer(const void* data, unsigned int sizeInBytes, unsigned int bindingBase, GLenum GLBufferMode) //DOES NOT UNBIND BUFFER FOR THE GPU CALL SAVING, IT SHOULD BE EASY TO WORK WITH THIS THOUGH
	: m_BindingBase(bindingBase)
{
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_rendererID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeInBytes, data, GLBufferMode);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_BindingBase, m_rendererID);

}

ShaderStorageBuffer::~ShaderStorageBuffer()
{
	glDeleteBuffers(1, &m_rendererID);
}

void ShaderStorageBuffer::Bind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_rendererID);
}

void ShaderStorageBuffer::Unbind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBuffer::SetBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) const //DOES NOT UNBIND BUFFER
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_rendererID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeInBytes, data, GLBufferMode);
}

void ShaderStorageBuffer::UpdateBufferSection(const void* data, unsigned int sizeInBytes, unsigned int offset) const //DOES NOT UNBIND BUFFER
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_rendererID);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeInBytes, data);
}

