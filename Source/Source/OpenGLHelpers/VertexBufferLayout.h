#include <vector>
#include <assert.h>

#include <glew.h>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalised;

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

	VertexBufferElement(unsigned int type, unsigned int count, bool normalised)
		: type(type),
		count(count),
		normalised(normalised) {}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
	unsigned int m_IndividualElements;
public:
	VertexBufferLayout()
		: m_Stride(0), m_IndividualElements(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_IndividualElements += count;
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_IndividualElements += count;
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	/*template<>
	void Push<uint32_t>(unsigned int count)
	{
		m_IndividualElements += count;
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}*/

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_IndividualElements += count;
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	
	// length of all attributes specified, in bytes
	inline unsigned int GetStride() const { return m_Stride; }

	// if you did push<float>(4) and push<float>(5), this would return 9, because there are 9 floats (works for any type and multiple types simultaneously)
	inline unsigned int GetNumberOfIndividualElements() const { return m_IndividualElements; }};