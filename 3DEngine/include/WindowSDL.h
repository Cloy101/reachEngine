// WindowSDL.h

#ifndef WINDOWSDL_H
#define WINDOWSDL_H

#include <SDL.h>
#include <SDL_vulkan.h>
#include <stdexcept>
#include <iostream>

class WindowSDL
{
private:
	SDL_Window* windowSDL;

public:
	WindowSDL(const char* windowName, uint32_t width, uint32_t height, SDL_WindowFlags flag);

	SDL_Window* get_windowSDL() { return windowSDL; }

	~WindowSDL();


private:
	void createSDLWindow(const char* windowName, uint32_t width, uint32_t height, SDL_WindowFlags flag);
};

#endif // WINDOWSDL_H
