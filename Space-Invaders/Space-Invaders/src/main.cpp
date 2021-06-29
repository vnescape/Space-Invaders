//Source: https://www.glfw.org/documentation.html
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Game.h"
#include "Shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


int main(void)
{
    Game(640, 480);
    return 0;
}