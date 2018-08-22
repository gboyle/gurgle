
#include "renderer.hpp"

#include <iostream>
#include <iomanip>

void GLClearError()
{
    while (1)
    {
        GLenum error = glGetError();

        if (error == GL_NO_ERROR)
        {
            break;
        }
    }
}

bool GLCheckError(const char *function, const char *file, int line)
{
    bool ok = true;

    while (1)
    {
        GLenum error = glGetError();

        if (error == GL_NO_ERROR)
        {
            break;
        }

        std::cout << "[" << file << ":" << line << " error 0x" << std::hex << std::setw(4) << std::setfill('0') << error << "] " << function << "\n ";
        ok = false;
    }

    return ok;
}