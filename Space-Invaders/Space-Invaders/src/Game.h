#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

enum GameState {
	GAMEPLAY,
	MENU,
	WIN,
};

class Game
{
private:
	GLFWwindow* window;
public:
	GameState m_State;
	unsigned int m_Width, m_Height;

	Game(unsigned int width, unsigned int height);
	~Game();
	int Init();
	void ProcessInput();
	void UpdateState();
	void Render();
};