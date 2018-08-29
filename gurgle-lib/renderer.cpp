
#include "renderer.hpp"

#include <iostream>
#include <iomanip>

//////////////////////////////////////////////////////////////////////////

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

//////////////////////////////////////////////////////////////////////////

void Renderer::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(VertexArray const &vertex_array, IndexBuffer const &index_buffer, Shader const &shader) const
{
    shader.bind();
    vertex_array.bind();
    index_buffer.bind();

    GLCall(glDrawElements(GL_TRIANGLES, index_buffer.getCount(), GL_UNSIGNED_INT, nullptr));
}

//////////////////////////////////////////////////////////////////////////

void GLBreak()
{
    int x = 0;
}

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

        std::cout << "[" << file << ":" << line << " error 0x"
                  << std::hex << std::setw(4) << std::setfill('0')
                  << error << std::dec << "] " << function << "\n ";

        ok = false;
    }

    return ok;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
