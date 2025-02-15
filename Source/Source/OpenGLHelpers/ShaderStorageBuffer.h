#include "glew.h"

class ShaderStorageBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_BindingBase;

public:
	ShaderStorageBuffer(const void* data, unsigned int sizeInBytes, unsigned int bindingBase, GLenum GLBufferMode);
	~ShaderStorageBuffer();

	void Bind() const;
	void Unbind() const;

	void SetBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) const;
	void UpdateBufferSection(const void* data, unsigned int sizeInBytes, unsigned int offset) const;
};