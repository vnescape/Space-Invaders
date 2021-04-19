//Source: https://www.glfw.org/documentation.html
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int CompileShader(unsigned int type, const std::string& source)
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
        delete [] message;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Initialize GLEW after creating a valid OpenGL context
    if (glewInit() != 0)
        return -1;

    // Print current OpenGL  version
    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f,
    };

    unsigned int BufferID;
    glGenBuffers(1, &BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // "stride" is a vertex attribute, whereas the "pointer" points into one vertex attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}