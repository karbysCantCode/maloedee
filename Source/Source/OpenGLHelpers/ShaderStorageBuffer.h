#include "glew.h"

class ShaderStorageBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_BindingBase;

public:
	ShaderStorageBuffer(const void* data, unsigned int sizeInBytes, unsigned int bindingBase, GLenum GLBufferMode);
	inline ~ShaderStorageBuffer() { glDeleteBuffers(1, &m_rendererID); }

	inline void Bind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_rendererID); }
	inline void Unbind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); }

	void SetBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) const;
	void UpdateBufferSection(const void* data, unsigned int sizeInBytes, unsigned int offset) const;
};