
#include "shader.hpp"
#include "renderer.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

//////////////////////////////////////////////////////////////////////////

Shader::Shader(std::string const &filepath)
    : m_renderer_id(0), m_filepath(filepath)
{
    ShaderProgramSource shader_sources = parseShader(m_filepath);

    m_renderer_id = createShader(shader_sources.VertexSource, shader_sources.FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_renderer_id);
}

//////////////////////////////////////////////////////////////////////////

void Shader::bind() const
{
    GLCall(glUseProgram(m_renderer_id));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

//////////////////////////////////////////////////////////////////////////

ShaderProgramSource Shader::parseShader(const std::string &filepath)
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

unsigned int Shader::compileShader(unsigned int type, const std::string &source)
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

unsigned int Shader::createShader(std::string const &vertexShader, std::string const &fragmentShader)
{
    // std::cout << "-------------- VertexSource --------------" << '\n';
    // std::cout << vertexShader << '\n';
    // std::cout << "-------------- FragmentSource --------------" << '\n';
    // std::cout << fragmentShader << '\n';

    unsigned int program_id = glCreateProgram();

    unsigned int vs_id = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs_id = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

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

//////////////////////////////////////////////////////////////////////////

int Shader::getUniformLocation(std::string const &name)
{
    auto it = m_uniform_location_cache.find(name);

    if (it != m_uniform_location_cache.end())
    {
        return it->second;
    }

    GLCall(int location = glGetUniformLocation(m_renderer_id, name.c_str()));

    if (location < 0)
    {
        std::cout << "warning: uniform " << name << " doesn't exist\n";
    }

    m_uniform_location_cache[name] = location;

    return location;
}

void Shader::setUniform4f(std::string const &name, float v0, float v1, float v2, float v3)
{
    int location = getUniformLocation(name);

    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

//////////////////////////////////////////////////////////////////////////
