// VK_DebugMessenger.h

#ifndef VK_DebugMessenger_H
#define VK_DebugMessenger_H

#include "VK_Headers.h"

class VK_DebugMessenger
{
private:
	VkDebugUtilsMessengerEXT debugMessenger;
	VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo;
	VkInstance vkInstance;

public:
	// Constructor of VK_DebugMessenger
	VK_DebugMessenger(VkInstance vkInstance);
	// Function to specify the information about message severity and message types
	static VkDebugUtilsMessengerCreateInfoEXT createDebugMessengerCreateInfo();

	~VK_DebugMessenger();

private:
	// Function to display the Vulkan errors withn Validation layers
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
															VkDebugUtilsMessageTypeFlagsEXT messageType,
															const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
															void* pUserData);
	// Function to create the Vulkan debug messenger
	void createDebugMessenger(VkInstance instance);
	// Function to specify the debug Vulkan extensios
	VkResult createDebugUtilsMessengerEXT(VkInstance instance,
											const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
											const VkAllocationCallbacks* pAllocator,
											VkDebugUtilsMessengerEXT* pDebugMessenger);

	// Function to destroy Vulkan debug messenger
	void destroyDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
								const VkAllocationCallbacks* pAllocator);
	
};

#endif // VK_DebugMessenger_H
