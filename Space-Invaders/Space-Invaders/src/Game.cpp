#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
    :m_Width(width), m_Height(height), m_State(GAMEPLAY)
{
    Game::Init();
    Game::Render();
}

Game::~Game()
{
}

int Game::Init()
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(m_Width, m_Height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // turns on VSync
    glfwSwapInterval(1);

    // Initialize GLEW after creating a valid OpenGL context
    if (glewInit() != 0)
        return -1;

    // Print current OpenGL  version
    std::cout << glGetString(GL_VERSION) << std::endl;
    return 1;
}

void Game::ProcessInput(float deltaTime)
{
}

void Game::UpdateState(float deltaTime)
{
}

void Game::Render()
{

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

    VertexArray va;

    // Generate, bind and fill VertexBuffer
    VertexBuffer vb(positions, sizeof(positions));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    // Creating and using a index buffer to refrence vertecis and avoid duplicates (Index Buffer)
    IndexBuffer ib(indices, sizeof(indices));

    // loading the shader
    Shader shader;
    shader.ShaderSrc = shader.ParseShader("res/shaders/Triangle.shader");

    // compiling a program based on the shader
    GLCall(shader.program = shader.CreateShader(shader.ShaderSrc.VertexSource,\
                                                shader.ShaderSrc.FragmentSource));
    // bound the shader, so that the uniform will be applied to this shader
    GLCall(glUseProgram(shader.program));

    // retrieves the id of the variable "u_Color"
    GLCall(int u_location = glGetUniformLocation(shader.program, "u_Color"));
    ASSERT(u_location != -1);
    // define variable "u_Color"
    GLCall(glUniform4f(u_location, 0.0, 1.0, 0.0, 1.0));

    float b = 0.0f;
    float r = 0.0f;
    float increment = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // modifies the "u_color" variable every frame
        GLCall(glUniform4f(u_location, r, 1.0, b, 1.0));

        va.Bind();
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr));

        if (r <= 0.0f || b <= 0.0f)
        {
            increment = 0.005f;
        }
        else if (r >= 1.0f || b >= 1.0f)
        {
            increment = -0.005f;
        }
        b += increment;
        r += increment;

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }
    glfwTerminate();
}

