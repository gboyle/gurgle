
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <signal.h>

// see https://www.glfw.org/documentation.html
// see https://www.youtube.com/watch?v=OR4fNpBjmq8
// see http://glew.sourceforge.net/
// see http://docs.gl/
// see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageCallback.xhtml
// see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetError.xhtml

#define ASSERT(x)       \
    if (!(x))           \
    {                   \
        raise(SIGTRAP); \
    }

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

static void GLClearError()
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

static bool GLCheckError(const char *function, const char *file, int line)
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
    GLCall(glShaderSource(id, 1, &src, nullptr));

    GLCall(glCompileShader(id));

    int result;
    // i => integer, v => vector
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        // did not compile

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        // allocate memory on the stack dynamically
        char *message = (char *)alloca(length * sizeof(char));

        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << " compilation failure : " << message << '\n';

        GLCall(glDeleteShader(id));

        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program_id = glCreateProgram();

    unsigned int vs_id = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs_id = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program_id, vs_id));
    GLCall(glAttachShader(program_id, fs_id));

    GLCall(glLinkProgram(program_id));

    int result;
    // i => integer, v => vector
    GLCall(glGetProgramiv(program_id, GL_LINK_STATUS, &result));
    if (result == GL_FALSE)
    {
        // did not link

        int length;
        GLCall(glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length));

        // allocate memory on the stack dynamically
        char *message = (char *)alloca(length * sizeof(char));

        GLCall(glGetProgramInfoLog(program_id, length, &length, message));

        std::cout << "program link failure : " << message << '\n';

        GLCall(glDeleteProgram(program_id));

        return 0;
    }

    GLCall(glValidateProgram(program_id));

    GLCall(glGetProgramiv(program_id, GL_VALIDATE_STATUS, &result));
    if (result == GL_FALSE)
    {
        // did not link

        int length;
        GLCall(glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length));

        // allocate memory on the stack dynamically
        char *message = (char *)alloca(length * sizeof(char));

        GLCall(glGetProgramInfoLog(program_id, length, &length, message));

        std::cout << "program link failure : " << message << '\n';

        GLCall(glDeleteProgram(program_id));

        return 0;
    }

    GLCall(glDeleteShader(vs_id));
    GLCall(glDeleteShader(fs_id));

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
    window = glfwCreateWindow(750, 750, "Hello World", NULL, NULL);
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

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

    GLClearError();

    // thanks to Henuindor
    GLuint vertexArrayID;
    GLCall(glGenVertexArrays(1, &vertexArrayID));
    GLCall(glBindVertexArray(vertexArrayID));

    // specify the vertices
    float positions[] = {
        -0.5f, -0.5f, // lower left
        0.5f, -0.5f,  // lower right
        0.5f, 0.5f,   // upper right
        -0.5f, 0.5f,  // upper left
    };

    // generate buffer and return id
    unsigned int buffer_id;
    GLCall(glGenBuffers(1, &buffer_id));

    // select the buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer_id));

    GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

    // specify the composition/layout of each vertex
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    GLCall(glEnableVertexAttribArray(0));

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));

    // select the buffer
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    auto shader_sources = ParseShader("res/shaders/basic.glsl"); // TODO

    // std::cout << "-------------- VertexSource --------------" << '\n';
    // std::cout << shader_sources.VertexSource << '\n';
    // std::cout << "-------------- FragmentSource --------------" << '\n';
    // std::cout << shader_sources.FragmentSource << '\n';

    unsigned int program_id = CreateShader(shader_sources.VertexSource, shader_sources.FragmentSource);

    GLCall(glUseProgram(program_id));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(program_id);

    glfwTerminate();

    return 0;
}
