#include "Shader.h"

// Parsing custom ".shader" files
ShaderSource ParseShader(const std::string& filepath)
{

    std::ifstream stream(filepath);

    enum class ShaderType
    {
        // Using names to reference to indices in ss[]
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line))
    {
        // find magic string (parse header)
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        // parse content of source file if it isn't none
        else
        {
            if (type != ShaderType::NONE)
                ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int CompileShader(unsigned int type, const std::string& source)
{
    // unsigned int = GLuint
    // unsigned int is used here, so there are no abstractions by OpenGL
    unsigned int id = glCreateShader(type);

    // source.c_str() or &source[0]
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // debug code
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        // don't use alloca() because of stack overflow excepcion,
        // use on heap allocation instead
        char* message = NULL;
        message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader" << std::endl;
        std::cout << message << std::endl;
        delete[] message;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

// Attaching shaders, compiling and linking them into a program which the GPU can execute
unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    //glDetachShader();
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}