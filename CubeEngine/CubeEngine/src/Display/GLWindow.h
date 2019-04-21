#pragma once

#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <SDL2/SDL.h>

class GLWindow
{
public:
	GLWindow();
	~GLWindow();

	int Init(int width, int height, const char* title);
	void Clear(float r, float g, float b, float a);
	bool isClosed() { return _winClosed; }
	void Update();

protected:
	int initLevel;
	SDL_Window* _sdl_window;
	SDL_GLContext _gl_context;
	bool _winClosed;
};

#endif // GLWINDOW_H