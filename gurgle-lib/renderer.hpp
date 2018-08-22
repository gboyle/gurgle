#pragma once

#include <GL/glew.h>

#define ASSERT(x)                                      \
    if (!(x))                                          \
    {                                                  \
        throw std::runtime_error("assertion failure"); \
    }

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

void GLClearError();
bool GLCheckError(const char *function, const char *file, int line);