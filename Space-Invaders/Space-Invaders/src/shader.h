#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

struct ShaderSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
public:

    unsigned int program;
    ShaderSource ShaderSrc;
    Shader();
    ~Shader();

    ShaderSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
};