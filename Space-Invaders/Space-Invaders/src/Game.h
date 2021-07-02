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
#include "VertexArray.h"
#include "IndexBuffer.h"



class Game
{
private:
	GLFWwindow* window;
	enum GameState {
		GAMEPLAY,
		MENU,
		WIN,
	};
public:
	GameState m_State;
	unsigned int m_Width, m_Height;

	Game(unsigned int width, unsigned int height);
	~Game();
	int Init();
	void ProcessInput(float deltaTime);
	void UpdateState(float deltaTime);
	void Render();
};