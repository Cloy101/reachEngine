// VK_Application.cpp

#ifndef VK_Application_CPP
#define VK_Application_CPP

#include "VK_Application.h"


VK_Application::VK_Application()
{
#ifndef NDEBUG
	std::cout << "VK_Application()" << std::endl;
#endif // !NDEBUG

 // 1. Setup video properties
	Setup_Video setupVideo;

 // 2. Create the window
 #ifdef LibrarySDL
	initSDL();
	WindowSDL window("REACH_SDL_VULKAN", setupVideo.get_screenWidth(), setupVideo.get_screenHeight(), SDL_WINDOW_VULKAN);
 #endif //LibrarySDL

 // 3. Create the validation layers
	if (enableValidationLayers)
	{
		VK_ValidLayers vvlTemp;
		this->vvl = vvlTemp;
	}

 // 4. Create the VkInstance
 #ifdef LibrarySDL
	VK_Instance vkInstance(queryWindowVkExtensions(window.get_windowSDL()));
	//this->vkInstanse = &vkInstance;
 #endif //LibrarySDL

 // 5. Create the Debug Messenger
	VK_DebugMessenger vkDebugMessenger(vkInstance.get_vkInstanse());

 // 6. Create the VkSurfaceKHR
 #ifdef LibrarySDL
	VK_Surface<SDL_Window*> vkSurface(window.get_windowSDL(), vkInstance.get_vkInstanse());
 #endif //LibrarySDL

 // 7. Create Physical and logicval devices
	VK_Queues vkQueues;
	this->p_vkQueues = &vkQueues;
	VK_Devices vkDevices(vkInstance.get_vkInstanse(), vkSurface.get_vkSurface(), &vkQueues);
 
 // 8. Create the Vulkan SwapChain
 #ifdef LibrarySDL
	VK_SwapChain<SDL_Window*> vkSwapchain(window.get_windowSDL(), vkSurface.get_vkSurface(), vkDevices.get_gpu(), vkDevices.get_vkDevice());
 #endif //LibrarySDL
}



void VK_Application::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error ("ERROR::VK_Application::initSDL()::SDL_Library is undefined");
	}
}


template <typename Twindow>
std::vector<const char*> VK_Application::queryWindowVkExtensions(Twindow window) /////////////////// NEED TO MAKE THIS WUNCHION AS TEMPLATE
{
	uint32_t extensionCount = 0;

	std::vector<const char*> extensions;

	// Taking the number of available extensions from SDL_Window
#ifdef LibrarySDL
		SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);

		for (uint32_t i{}; i < extensionCount; ++i)
		{
			extensions.emplace_back(nullptr);
		}

		// Filling the array with names of available SDL_Window extensions
		SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensions.data());
#endif // LibrarySDL

	if (enableValidationLayers)
	{
		// Adding the VK_Debug_utils extension to the available SDL extensions
		extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}



VK_Application::~VK_Application()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_Application()" << std::endl;
	}

#ifdef LibrarySDL
	SDL_Quit();
#endif //LibrarySDL
}

#endif // VK_Application_CPP