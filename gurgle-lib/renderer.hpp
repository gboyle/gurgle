#pragma once

#include <GL/glew.h>

#include "vertex-array.hpp"
#include "index-buffer.hpp"
#include "shader.hpp"

//////////////////////////////////////////////////////////////////////////

class Renderer
{

  public:
    Renderer();
    ~Renderer();

    void clear() const;
    void draw(VertexArray const &vertex_array, IndexBuffer const &index_buffer, Shader const &shader) const;
};

//////////////////////////////////////////////////////////////////////////

#define ASSERT(x)  \
    if (!(x))      \
    {              \
        GLBreak(); \
    }

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

void GLBreak();
void GLClearError();
bool GLCheckError(const char *function, const char *file, int line);

//////////////////////////////////////////////////////////////////////////
