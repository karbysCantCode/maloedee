#include "glew.h"

#include <assert.h>
#include <vector>

class ShaderStorageBuffer
{
public:
	struct SSBOElement
	{
		unsigned int type;
		unsigned int count;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT:		    return sizeof(GLfloat);
			case GL_UNSIGNED_INT:   return sizeof(GLint);
			case GL_UNSIGNED_BYTE:	return sizeof(GLbyte);
			}
			assert(false);
			return 0;
		}
	};
private:
	unsigned int m_rendererID;
	unsigned int m_BindingBase;

	unsigned int m_Stride;
	std::vector<SSBOElement> m_Elements;

public:
	ShaderStorageBuffer(const void* data, unsigned int sizeInBytes, unsigned int bindingBase, GLenum GLBufferMode);
	inline ~ShaderStorageBuffer() { glDeleteBuffers(1, &m_rendererID); }

	inline void Bind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_rendererID); }
	inline void Unbind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); }

	void SetBuffer(const void* data, unsigned int sizeInBytes, GLenum GLBufferMode) const;
	void UpdateBufferSection(const void* data, unsigned int sizeInBytes, unsigned int offset) const;

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count);

	template<>
	void Push<unsigned int>(unsigned int count);

	template<>
	void Push<unsigned char>(unsigned int count);

	inline unsigned int GetStride() const { return m_Stride; }
	inline const std::vector<SSBOElement>& GetElements() const { return m_Elements; }
};