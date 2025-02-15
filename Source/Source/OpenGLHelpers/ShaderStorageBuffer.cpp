#include "ShaderStorageBuffer.h"

ShaderStorageBuffer::ShaderStorageBuffer(const void* data, unsigned int sizeInBytes, unsigned int bindingBase, GLenum GLBufferMode) //DOES NOT UNBIND BUFFER FOR THE GPU CALL SAVING, IT SHOULD BE EASY TO WORK WITH THIS THOUGH
	: m_BindingBase(bindingBase)
{
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_rendererID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeInBytes, data, GLBufferMode);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_BindingBase, m_rendererID);

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

template<>
void ShaderStorageBuffer::Push<float>(unsigned int count)
{
	m_Elements.push_back({ GL_FLOAT, count});
	m_Stride += count * SSBOElement::GetSizeOfType(GL_FLOAT);
}

template<>
void ShaderStorageBuffer::Push<unsigned int>(unsigned int count)
{
	m_Elements.push_back({ GL_UNSIGNED_INT, count});
	m_Stride += count * SSBOElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void ShaderStorageBuffer::ShaderStorageBuffer::Push<unsigned char>(unsigned int count)
{
	m_Elements.push_back({ GL_UNSIGNED_BYTE, count});
	m_Stride += count * SSBOElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

