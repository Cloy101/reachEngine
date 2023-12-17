// VK_Surface.h

#ifndef VK_Surface_H
#define VK_Surface_H

#include "VK_Headers.h"

template <typename Twindow>
class VK_Surface
{
private:
	VkSurfaceKHR vkSurface;
	VkInstance vkInstance;

public:
	// Constructor of VK_Surface to create surface with only SDL_Window
	VK_Surface(Twindow window, VkInstance instance);

	VkSurfaceKHR get_vkSurface() { return vkSurface; }

	~VK_Surface();

private:
	void createSurface(Twindow window, VkInstance instance);
};


template <typename Twindow>
VK_Surface<Twindow>::VK_Surface(Twindow window, VkInstance instance)
{
	createSurface(window, instance);
	this->vkInstance = instance;
}


template <typename Twindow>
void VK_Surface<Twindow>::createSurface(Twindow window, VkInstance instance)
{
#ifdef LibrarySDL
	if (!(SDL_Vulkan_CreateSurface(window, instance, &vkSurface)))
	{
		throw std::runtime_error("ERROR::VK_Surface::createSurface()::Failed to create window surface");
	}
#endif // LibrarySDL
}


template <typename Twindow>
VK_Surface<Twindow>::~VK_Surface()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_Surface()" << std::endl;
	}

	vkDestroySurfaceKHR(this->vkInstance, this->vkSurface, nullptr);
}

#endif // VK_Surface_H