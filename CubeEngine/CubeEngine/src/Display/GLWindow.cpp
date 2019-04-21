#include "GLWindow.h"
#include <Core/Core.h>
#include <GL/glew.h>

GLWindow::GLWindow()
{
	initLevel = 0;
}

int GLWindow::Init(int width, int height, const char* title)
{
	unsigned int status = SDL_Init(SDL_INIT_EVERYTHING);
	if (status != 0)
	{
		DEBUG_LOG("SDL_Init failed : %s\n", SDL_GetError());
		return -1;
	}
	DEBUG_LOG("SDL_Init successful\n");
	initLevel = 1;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (_sdl_window == NULL)
	{
		DEBUG_LOG("SDL_CreateWindow failed : %s\n", SDL_GetError());
		return -2;
	}
	DEBUG_LOG("SDL_CreateWindow successful\n");
	initLevel = 2;

	_gl_context = SDL_GL_CreateContext(_sdl_window);
	if (_gl_context == NULL)
	{
		DEBUG_LOG("SDL_GL_CreateContext failed : %s\n", SDL_GetError());
		return -3;
	}
	DEBUG_LOG("SDL_GL_CreateContext successful\n");
	initLevel = 3;

	status = glewInit();
	if (status != GLEW_OK)
	{
		DEBUG_LOG("glewInit failed : %s\n", glewGetErrorString(status));
		return -4;
	}
	DEBUG_LOG("glewInit succesful\n");
	initLevel = 4; // everything initialized successfully

	_winClosed = false;
	return 0;
}

GLWindow::~GLWindow()
{
	switch (initLevel)
	{
	case 4:
	case 3:
		SDL_GL_DeleteContext(_gl_context);
	case 2:
		SDL_DestroyWindow(_sdl_window);
	case 1:
		SDL_Quit();
	default:
		break;
	}
}

void GLWindow::Clear(float r, float g, float b, float a)
{
	if (initLevel < 4) return;

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLWindow::Update()
{
	if (initLevel < 4) return;

	SDL_GL_SwapWindow(_sdl_window);

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) _winClosed = true;
	}
}