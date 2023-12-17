// VK_DebugMessenger.cpp

#ifndef VK_DebugMessenger_CPP
#define VK_DebugMessenger_CPP

#include <VK_DebugMessenger.h>

VK_DebugMessenger::VK_DebugMessenger(VkInstance vkInstance)
{
#ifndef NDEBUG
	std::cout << "VK_DebugMessenger()" << std::endl;
#endif // !NDEBUG

	createDebugMessenger(vkInstance);
	this->vkInstance = vkInstance;
}


VkDebugUtilsMessengerCreateInfoEXT VK_DebugMessenger::createDebugMessengerCreateInfo()
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
									VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
									VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
								VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
								VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	return createInfo;
}


VKAPI_ATTR VkBool32 VKAPI_CALL VK_DebugMessenger::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
																	VkDebugUtilsMessageTypeFlagsEXT messageType,
																	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
																	void* pUserData)
{
	std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
	return VK_FALSE;
}


void VK_DebugMessenger::createDebugMessenger(VkInstance instance)
{
	if (!enableValidationLayers) return;
	VkDebugUtilsMessengerCreateInfoEXT createInfo = createDebugMessengerCreateInfo();

	if (createDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
	{
		throw std::runtime_error("ERROR::Screen::setupDebugMessenger()::Failed to set up debug messenger");
	}
}


VkResult VK_DebugMessenger::createDebugUtilsMessengerEXT(VkInstance instance,
															const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
															const VkAllocationCallbacks* pAllocator,
															VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}


void VK_DebugMessenger::destroyDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
												const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr)
	{
		func(instance, debugMessenger, pAllocator);
	}
}


VK_DebugMessenger::~VK_DebugMessenger()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_DebugMessenger()" << std::endl;
	}
	destroyDebugMessenger(this->vkInstance, this->debugMessenger, nullptr);
}

#endif // VK_DebugMessenger_CPP