#include <iostream>

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
#define GLAssertError() ASSERT(GLLogCall( __FILE__, __LINE__))
