
#include "game.hpp"

#include "renderer.hpp"
#include "vertex-layout.hpp"
#include "vertex-array.hpp"
#include "vertex-buffer.hpp"
#include "index-buffer.hpp"
#include "shader.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

int gurgle()
{

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(750, 750, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // must occur after we've created a valid OpenGL rendering context
    //glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Unable to initialize glew\n";
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

    GLClearError();

    {
        // scope to deallocate OpenGL related locals before glfwTerminate

        // specify the vertices
        float positions[] = {
            -0.5f, -0.5f, // lower left
            0.5f, -0.5f,  // lower right
            0.5f, 0.5f,   // upper right
            -0.5f, 0.5f,  // upper left
        };

        VertexBuffer vertex_buffer(positions, 4 * 2 * sizeof(float));

        VertexLayout vertex_layout;
        vertex_layout.pushFloat(2);

        VertexArray vertex_array;
        vertex_array.addBuffer(vertex_buffer, vertex_layout);

        // specify the composition/layout of each vertex
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0)); // links buufer to to vao

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

        IndexBuffer index_buffer(indices, 2 * 3);

        Shader shader("res/shaders/basic.glsl");
        //Shader shader("../../res/shaders/basic.glsl");
        shader.bind();
        shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        // unbind everything
        vertex_array.unbind();
        shader.unbind();
        vertex_array.unbind();
        index_buffer.unbind();

        Renderer renderer;

        float r = 0.0f;
        float inc = 0.01f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            shader.bind();
            shader.setUniform4f("u_Color", r, 0.3f, 0.4f, 1.0f);

            renderer.draw(vertex_array, index_buffer, shader);

            r += inc;
            if (r > 1.0f || r < 0.0f)
            {
                inc = -inc;
                r += inc;
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();

    return 0;
}