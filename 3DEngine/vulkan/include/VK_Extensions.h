// VK_Extensions.h

#ifndef VK_Extensions_H
#define VK_Extensions_H

#include "VK_Headers.h"
#include <set>

// This constant intended for enumeration of required device extensions
static const std::vector<const char*> DEVICE_EXTENSIONS = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

class VK_Extensions
{
private:
	// The list of extensions provided by current version of Vulkan API
	std::vector<VkExtensionProperties> availableVkExtensions;

public:
	VK_Extensions();

	std::vector<VkExtensionProperties> get_availableVkExtensions() { return availableVkExtensions; }
	// Function to display the extensions provided by current version of Vulkan API
	void showAvailableVkExtensions();
	// Function to query the supported Vulcan extensions from GPU
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	~VK_Extensions();

private:
	// Function to query the extensions from Vulkan API
	void queryVkExtensions();

};

#endif // VK_Extensions_H