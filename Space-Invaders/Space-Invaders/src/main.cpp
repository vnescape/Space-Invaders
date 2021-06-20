//Source: https://www.glfw.org/documentation.html
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "shader.h"

// Assert for breaking debugger in code. "__debugbreak" specific for MSVC
#define ASSERT(x) if (!(x)) __debugbreak();

// Wrap a function around error checking
// "#x" passes the function name as a string
#define GLCall(x) GLClearError(); x;\
ASSERT(GLLogError(#x, __FILE__, __LINE__));

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogError(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << 
        " " << file << ":"<< line << std::endl;
        return false;
    }
    return true;
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

    float positions[] = {
        -0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
         0.0f,  0.9f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        3, 2, 1,
        1, 3, 4,
    };

    // Generating, binding and filling a buffer to be send to the GPU
    unsigned int BufferID;
    GLCall(glGenBuffers(1, &BufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    // "stride" is a vertex attribute, whereas the "pointer" points into one vertex attribute
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
    GLCall(glEnableVertexAttribArray(0));

    // Creating and using a index buffer to refrence vertecis and avoid duplicates
    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    // loading the shader
    ShaderSource source = ParseShader("res/shaders/Triangle.shader");

    /* Print Source for debugging
    std::cout << source.VertexSource << std::endl;
    std::cout << source.FragmentSource << std::endl;
    */

    // compiling a program based on the shader
    GLCall(unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource));
    // bound the shader, so that the uniform will be applied to this shader
    GLCall(glUseProgram(shader));

    // retrieves the id of the variable "u_Color"
    GLCall(int u_location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(u_location != -1);
    // define variable "u_Color"
    GLCall(glUniform4f(u_location, 0.0, 1.0, 0.0, 1.0));

    float b = 0.0f;
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while(!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // modifies the "u_color" variable every frame
        GLCall(glUniform4f(u_location, r, 1.0, b, 1.0));
        GLCall(glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr));

        if (b > 1.0f || r > 1.0f)
        {
            b = 0;
            r = 0;
        }
        else
        {
            b += increment;
            r += increment;
        }

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}