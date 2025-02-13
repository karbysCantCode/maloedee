#include "glew.h"
#include "glfw3.h"
#include "glfw3native.h"

class VertexBuffer
{
private:
	unsigned int m_rendererID;

public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetBuffer();
	void UpdateBuffer();
};