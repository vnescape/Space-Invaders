#pragma once
#include <GL/glew.h>

// Assert for breaking debugger in code. "__debugbreak" specific for MSVC
#define ASSERT(x) if (!(x)) __debugbreak();

// Wrap a function around error checking
// "#x" passes the function name as a string
#define GLCall(x) GLClearError(); x;\
ASSERT(GLLogError(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogError(const char* function, const char* file, int line);
