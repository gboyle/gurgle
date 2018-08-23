
#include "game.hpp"

#include "renderer.hpp"
#include "vertex-layout.hpp"
#include "vertex-array.hpp"
#include "vertex-buffer.hpp"
#include "index-buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
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

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glBlendEquation(GL_FUNC_ADD));

        // specify the vertices
        float vertices[] = {
            100.0f, 100.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // lower left
            200.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // lower right
            200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // upper right
            100.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // upper left
        };

        VertexBuffer vertex_buffer(vertices, sizeof(vertices));

        VertexLayout vertex_layout;
        vertex_layout.pushFloat(2);
        vertex_layout.pushFloat(3);
        vertex_layout.pushFloat(2);

        VertexArray vertex_array;
        vertex_array.addBuffer(vertex_buffer, vertex_layout);

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

        IndexBuffer index_buffer(indices, 2 * 3);

        glm::mat4 projection_matrix = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, +1.0f); // left right bottom top near far
        glm::mat4 view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(300, 0, 0));
        glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
        glm::mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix; // column major order => reverse order

        Texture texture("res/textures/globe-scene-fish-bowl-pngcrush.png");
        texture.bind();

        Shader shader("res/shaders/basic.glsl");
        shader.bind();
        shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.setUniform1i("u_texture", 0);
        shader.setUniformMat4f("u_mvp", mvp_matrix);

        Renderer renderer;

        // unbind everything
        vertex_array.unbind();
        shader.unbind();
        vertex_array.unbind();
        index_buffer.unbind();

        float r = 0.0f;
        float inc = 0.01f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            shader.bind();
            shader.setUniform4f("u_color", r, 0.3f, 0.4f, 1.0f);

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
