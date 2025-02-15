#include <iostream>
#include <vector>
#include "glew.h"

#define debug() (std::cout << __LINE__ << std::endl)


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {

    }
};

static bool GLLogCall(const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] (" << error << ")" << ' ' << file << ':' << line << std::endl;
        return false;
    }
    return true;
}

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLAssertError() ASSERT(GLLogCall( __FILE__, __LINE__));

template<typename T>
void SpillVectorContentsGently(std::vector<T>& vector, unsigned int entriesPerLine)
{
    for (int i = 0; i < vector.size() / entriesPerLine; i++)
    {
        for (int x = 0; x < entriesPerLine; x++)
        {
            std::cout << vector[(i * entriesPerLine) + x] << " ";
        }
        std::cout << std::endl;
    }
}
