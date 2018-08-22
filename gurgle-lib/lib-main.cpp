
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// see https://www.glfw.org/documentation.html
// see https://www.youtube.com/watch?v=OR4fNpBjmq8
// see http://glew.sourceforge.net/
// see http://docs.gl/

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);

    char const *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);

    int result;
    // i => integer, v => vector
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        // did not compile

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        // allocate memory on the stack dynamically
        char *message = (char *)alloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);

        std::cout << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << " compilation failure : " << message << '\n';

        glDeleteShader(id);

        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program_id = glCreateProgram();

    unsigned int vs_id = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs_id = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program_id, vs_id);
    glAttachShader(program_id, fs_id);

    glLinkProgram(program_id);
    glValidateProgram(program_id);

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    return program_id;
}

int gurgle()
{

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // must occur after we've created a valid OpenGL rendering context
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Unable to initialize glew\n";
    }

    std::cout << glGetString(GL_VERSION) << '\n';

    // new style

    // generate buffer and return id
    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id);

    // select the buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

    // specify the triangle vertices
    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f};

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // specify the composition/layout of each vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0,0.0,0.0,1.0);\n"
        "}\n";

    unsigned int program_id = CreateShader(vertexShader, fragmentShader);
    glUseProgram(program_id);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // old style, immediate mode
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f(0.0f, 0.5f);
        // glVertex2f(0.5f, -0.5f);
        // glEnd();

        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES,3 ,)

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}