
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// see https://www.glfw.org/documentation.html
// see https://www.youtube.com/watch?v=OR4fNpBjmq8
// see http://glew.sourceforge.net/
// see http://docs.gl/

void verify(const char *message)
{
    unsigned int error = glGetError();

    if (error != GL_NO_ERROR)
    {
        std::cout << message << error << '\n';
        exit(1);
    }
}

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);
    if (!stream.is_open())
    {
        return {};
    }

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    ShaderType shader_type = ShaderType::NONE;
    std::stringstream shader_source[2];

    std::string line;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("#shader vertex") != std::string::npos)
            {
                shader_type = ShaderType::VERTEX;
            }
            else if (line.find("#shader fragment") != std::string::npos)
            {
                shader_type = ShaderType::FRAGMENT;
            }
            else
            {
                shader_type = ShaderType::NONE;
            }
        }
        else if (shader_type != ShaderType::NONE)
        {

            shader_source[static_cast<int>(shader_type)] << line << '\n';
        }
    }

    return {shader_source[0].str(), shader_source[1].str()};
}

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
    verify("glCreateProgram failed: ");

    unsigned int vs_id = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs_id = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program_id, vs_id);
    glAttachShader(program_id, fs_id);

    glLinkProgram(program_id);

    int result;
    // i => integer, v => vector
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        // did not link

        int length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);

        // allocate memory on the stack dynamically
        char *message = (char *)alloca(length * sizeof(char));

        glGetProgramInfoLog(program_id, length, &length, message);

        std::cout << "program link failure : " << message << '\n';

        glDeleteProgram(program_id);

        return 0;
    }

    glValidateProgram(program_id);
    verify("glValidateProgram failed: ");

    glGetProgramiv(program_id, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE)
    {
        // did not link

        int length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);

        // allocate memory on the stack dynamically
        char *message = (char *)alloca(length * sizeof(char));

        glGetProgramInfoLog(program_id, length, &length, message);

        std::cout << "program link failure : " << message << '\n';

        glDeleteProgram(program_id);

        return 0;
    }

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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
    //glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Unable to initialize glew\n";
    }

    std::cout << glGetString(GL_VERSION) << '\n';

    // new style

    // reset error flag
    glGetError();

    // thanks to Henuindor
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // generate buffer and return id
    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id);
    verify("glGenBuffers failed: ");

    // select the buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    verify("glBindBuffer failed: ");

    // specify the triangle vertices
    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f};

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    verify("glBufferData failed: ");

    // specify the composition/layout of each vertex
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    verify("glVertexAttribPointer failed: ");

    glEnableVertexAttribArray(0);
    verify("glEnableVertexAttribArray failed: ");

    auto shader_sources = ParseShader("../res/shaders/basic.glsl"); // TODO

    std::cout << "-------------- VertexSource --------------" << '\n';
    std::cout << shader_sources.VertexSource << '\n';
    std::cout << "-------------- FragmentSource --------------" << '\n';
    std::cout << shader_sources.FragmentSource << '\n';

    unsigned int program_id = CreateShader(shader_sources.VertexSource, shader_sources.FragmentSource);

    glUseProgram(program_id);
    verify("glUseProgram failed: ");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        verify("glClear failed: ");

        // old style, immediate mode
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f(0.0f, 0.5f);
        // glVertex2f(0.5f, -0.5f);
        // glEnd();

        glDrawArrays(GL_TRIANGLES, 0, 3);
        verify("glDrawArrays failed: ");

        //glDrawElements(GL_TRIANGLES,3 ,)

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(program_id);

    glfwTerminate();

    return 0;
}
