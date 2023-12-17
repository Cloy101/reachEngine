// VK_SwapChain.h

#ifndef VK_SwapChain_H
#define VK_SwapChain_H

#include <algorithm>
#include "VK_Headers.h"
#include "VK_QueueFamilies.h"
#include "VK_SwapChainSupportDetails.h"
#include "VK_ImageView.h"


template<typename Twindow>
class VK_SwapChain
{
private:
	VkSwapchainKHR vkSwapchain;
	VkFormat vkSwapchainFormat;
	VkExtent2D vkSwapchainExtend;
	std::vector<VkImage> swapchainImages;
	std::vector<VK_ImageView> swapchainImageViews;

	VkDevice vkDevice;

public:
	// Constructor of VK_SwapChain
	VK_SwapChain(Twindow window, VkSurfaceKHR vkSurface, VkPhysicalDevice gpu, VkDevice vkDevice);

	VkSwapchainKHR get_vkSwapchain() { return vkSwapchain; }
	VkFormat get_vkSwapchainFormat() { return vkSwapchainFormat; }

	~VK_SwapChain();
private:
	// Function to create Vulkan Swapchain
	void createSwapChain(Twindow window, VkSurfaceKHR vkSurface, VkPhysicalDevice gpu, VkDevice vkDevice);
	// Function to define the format mode of the Swapchain supported by GPU
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	// Function to ge the present mode supported by GPU
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	// Function to get surface extend from window for the Swapchain
	VkExtent2D chooseSwapExtent(Twindow window, const VkSurfaceCapabilitiesKHR& capabilities);
	// Function to create the list of Swapchain image views
	void createSwapImageViews(VkDevice vkDevice);
};

#include "../3DEngine/vulkan/src/VK_SwapChain.cpp"

#endif // VK_SwapChain_H
