// VK_SwapChainSupportDetails.h

#ifndef VK_SwapChainSupportDetails_H
#define VK_SwapChainSupportDetails_H

#include "VK_Headers.h"

struct VK_SwapChainSupportDetails
{
	// min/max numbers of images in the SwapChain
	VkSurfaceCapabilitiesKHR capabilities;
	// Format of pixels and color space
	std::vector<VkSurfaceFormatKHR> formats;
	// Available operation modes
	std::vector<VkPresentModeKHR> presentModes;

	// Function to get the support detailes of the Vulkan Swap Chain of GPU
	static VK_SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice gpu, VkSurfaceKHR vkSurface)
	{
		VK_SwapChainSupportDetails temp;

		// Getting the SwapChan capabilities 
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, vkSurface, &temp.capabilities);

		// Getting the supported formats of the window surface
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, vkSurface, &formatCount, nullptr);
		if (formatCount != 0)
		{
			temp.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, vkSurface, &formatCount, temp.formats.data());
		}

		// Getting the supported operation modes
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(gpu, vkSurface, &presentModeCount, nullptr);
		if (presentModeCount != 0)
		{
			temp.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(gpu, vkSurface, &presentModeCount, temp.presentModes.data());
		}

		return temp;
	}
};

#endif // VK_SwapChainSupportDetails_H
