// VK_Instance.cpp

#ifndef VK_Instance_CPP
#define VK_Instance_CPP

#include "VK_Instance.h"

VK_Instance::VK_Instance(std::vector<const char*> VkExtensions)
{
#ifndef NDEBUG
	std::cout << "VK_Instance()" << std::endl;
#endif // !NDEBUG

	createVkInstance(VkExtensions);
}


void VK_Instance::createVkInstance(std::vector<const char*> VkExtensions)
{

	// Creating the base information about app to provide it to the driver of the device
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = static_cast<const char*>(Main_AppInfo::APP_NAME.c_str());
	appInfo.applicationVersion = VK_MAKE_VERSION(Main_AppInfo::APP_MAJOR_VERSION, Main_AppInfo::APP_MINOR_VERSION, 0);
	appInfo.pEngineName = static_cast<const char*>(Main_AppInfo::GRAPHICS_ENGINE_NAME.c_str());
	appInfo.engineVersion = VK_MAKE_VERSION(Main_AppInfo::GRAPHICS_ENGINE_MAJOR_VERSION, Main_AppInfo::GRAPHICS_ENGINE_MINOR_VERSION, 0);
	appInfo.apiVersion = VK_API_VERSION_1_3;
	appInfo.pNext = nullptr;

	// Creating the structure, that provide to the driver information about global extensions such as ______ and global validation layers, that used for catching the errors
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.pApplicationInfo = &appInfo;

	// Taking the list of available extensions from SDL2_Window for Vulkan
	//std::vector<const char*> extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(VkExtensions.size());
	createInfo.ppEnabledExtensionNames = VkExtensions.data();

	//VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
		createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();

		VkDebugUtilsMessengerCreateInfoEXT temp = VK_DebugMessenger::createDebugMessengerCreateInfo();
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &temp;
	}
	else
	{
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}

	// Creating  the VkInstance - the main point to bind GPU and the app;
	if (vkCreateInstance(&createInfo, nullptr, &vkInstanse) != VK_SUCCESS) 
	{
		throw std::runtime_error("ERROR::VK_Instance::createVkInstance()::Failed to create Vulkan instance");
	}
}


VK_Instance::~VK_Instance()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_Instance()" << std::endl;
	}

	vkDestroyInstance(vkInstanse, nullptr);
}

#endif // VK_Instance_CPP