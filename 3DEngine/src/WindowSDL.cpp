// WindowSDL.cpp

#ifndef WINDOWSDL_CPP
#define WINDOWSDL_CPP

#include "WindowSDL.h"

WindowSDL::WindowSDL(const char* windowName, uint32_t width, uint32_t height, SDL_WindowFlags flag)
{
#ifndef NDEBUG
	std::cout << "WindowSDL()" << std::endl;
#endif // !NDEBUG

	createSDLWindow(windowName, width, height, flag);
}


void WindowSDL::createSDLWindow(const char* windowName, uint32_t width, uint32_t height, SDL_WindowFlags flag)
{
	this->windowSDL = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(width),
		static_cast<int>(height), flag);

	if (!windowSDL)
	{
		throw std::runtime_error("ERROR::VK_Application::createSDLWindow()::SDL_Window isn't created");
	}
}


WindowSDL::~WindowSDL()
{
#ifndef NDEBUG
	std::cout << "~SDLWindow()" << std::endl;
#endif // NDEBUG

	SDL_DestroyWindow(windowSDL);
}

#endif // WINDOWSDL_CPP