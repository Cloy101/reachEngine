// VK_Application.h

#ifndef VK_Application_H
#define VK_Application_H

#include "VK_Headers.h"
#include "VK_DebugMessenger.h"
#include "VK_Instance.h"
#include "VK_Surface.h"
#include "VK_Queues.h"
#include "VK_Devices.h"
#include "VK_SwapChain.h"

class VK_Application
{
private:
	VK_ValidLayers vvl;
	VK_Queues* p_vkQueues;

public:
	// Constructor of a class VK_Application
	VK_Application();

	~VK_Application();

private:
	// Function to initialize the SDL video library
	void initSDL();
	// Function to query from the SDL_Window necessary Vulkan extensions
	template <typename Twindow>
	std::vector<const char*> queryWindowVkExtensions(Twindow window);
};

#endif // VK_Application_H