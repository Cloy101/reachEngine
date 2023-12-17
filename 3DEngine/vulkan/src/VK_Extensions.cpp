// VK_Extensions.cpp

#ifndef VK_Extensions_CPP
#define VK_Extensions_CPP

#include "VK_Extensions.h"

VK_Extensions::VK_Extensions()
{
#ifndef NDEBUG
	std::cout << "VK_Extensions()" << std::endl;
#endif // !NDEBUG

	queryVkExtensions();
}


void VK_Extensions::showAvailableVkExtensions()
{
	std::cout << "Available extensions:\n";
	for (const auto& extension : availableVkExtensions) {
		std::cout << '\t' << extension.extensionName << " version: " << extension.specVersion << '\n';
	}
	std::cout << std::endl;
}


void VK_Extensions::queryVkExtensions()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	// Allocating the necessary quantity of the memory to fill with the information of available extensions further 
	VkExtensionProperties temp;
	for (uint32_t i{}; i < extensionCount; i++)
	{
		availableVkExtensions.emplace_back(temp);
	}

	// This function enumerates supported extensions and their versions and fill the array with structures VkExtensionsProperties
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableVkExtensions.data());
}


bool VK_Extensions::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	// Creating the variable to get the quantity of supported extensions by the Physical Device
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	// Placing the available extensions to the list 
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	if (enableValidationLayers)
	{
		int i = 1;
		for (const auto& temp : availableExtensions)
		{
			std::cout << "Ext " << i << ": " << temp.extensionName << std::endl;
			++i;
		}
	}

	// Getting the list of names the extensions
	std::set<std::string> requiredExtensions(DEVICE_EXTENSIONS.begin(), DEVICE_EXTENSIONS.end());
	// Checking the supporting the extensions for the SwapChain
	for (const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}


VK_Extensions::~VK_Extensions()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_Extensions()" << std::endl;
	}
}

#endif // VK_Extensions_CPP