#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    unsigned int m_renderer_id;

    std::string m_filepath;

    std::unordered_map<std::string, int> m_uniform_location_cache;

    int getUniformLocation(std::string const &name);

    ShaderProgramSource parseShader(const std::string &filepath);
    unsigned int compileShader(unsigned int type, const std::string &source);
    unsigned int createShader(std::string const &vertexShader, std::string const &fragmentShader);

  public:
    explicit Shader(std::string const &filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(std::string const &name, float v0, float v1, float v2, float v3);
    void setUniform1i(std::string const &name, int v0);
};
