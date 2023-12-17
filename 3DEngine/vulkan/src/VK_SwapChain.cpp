// VK_SwapChain.cpp

#ifndef VK_SwapChain_CPP
#define VK_SwapChain_CPP

#include "VK_SwapChain.h"


template<typename Twindow>
VK_SwapChain<Twindow>::VK_SwapChain(Twindow window, VkSurfaceKHR vkSurface, VkPhysicalDevice gpu, VkDevice vkDevice)
{
#ifndef NDEBUG
	std::cout << "VK_SwapChain()" << std::endl;
#endif // !NDEBUG

	createSwapChain(window, vkSurface, gpu, vkDevice);
	createSwapImageViews(vkDevice);
}


template<typename Twindow>
void VK_SwapChain<Twindow>::createSwapChain(Twindow window, VkSurfaceKHR vkSurface, VkPhysicalDevice gpu, VkDevice vkDevice)
{
	VK_SwapChainSupportDetails swapChainSupport = VK_SwapChainSupportDetails::querySwapChainSupport(gpu, vkSurface);

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(window, swapChainSupport.capabilities);

	this->vkSwapchainFormat = surfaceFormat.format;
	this->vkSwapchainExtend = extent;

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
	{
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VK_QueueFamilies indices = VK_QueueFamilies::findQueueFamilies(gpu, vkSurface);
	uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value(), indices.transferFamily.value() };

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = vkSurface;

	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	if (indices.graphicsFamily != indices.presentFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE; // Difficult topic

	if (vkCreateSwapchainKHR(vkDevice, &createInfo, nullptr, &vkSwapchain))
	{
		throw std::runtime_error("ERROR::VK_SwapChain::createSwapChain()::Failed to create the Swap Chain");
	}

	// Getting the descriptors of the SwapChain Images
	vkGetSwapchainImagesKHR(vkDevice, vkSwapchain, &imageCount, nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(vkDevice, vkSwapchain, &imageCount, swapchainImages.data());

	this->vkDevice = vkDevice;
}


template<typename Twindow>
VkSurfaceFormatKHR VK_SwapChain<Twindow>::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	// Enumerate the available color formats for the Window Surface
	for (const auto& availableFormat : availableFormats)
	{
		// Finding the necessary format of color
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
		// If the necessary color format is unavailable, take the first format from the list
		return availableFormats[0];
	}
}


template<typename Twindow>
VkPresentModeKHR VK_SwapChain<Twindow>::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	// Enumerate the available present modes
	for (const auto& availablePresentMode : availablePresentModes)
	{
		// Finding the coincidence with the best mode that fits the triple buffering
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}
	// If the chosen mode is unavailable, take the mode, that available with any Physical Device, that supports the Vulkan API
	return VK_PRESENT_MODE_FIFO_KHR;
}


template<typename Twindow>
VkExtent2D VK_SwapChain<Twindow>::chooseSwapExtent(Twindow window, const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width == vkSwapchainExtend.width)
	{
		return capabilities.currentExtent;
	}
	else
	{
		// Getting the actual size of the SDL_Window in pixels
		int width, height;

	 #ifdef LibrarySDL
		SDL_GetWindowSizeInPixels(window, &width, &height);
	 #endif // LibrarySDL

		VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

		// Comparing the current window extent with min and max available window dimensions 
		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}


template<typename Twindow>
void VK_SwapChain<Twindow>::createSwapImageViews(VkDevice vkDevice)
{
	for (size_t i{}; i < swapchainImages.size(); ++i)
	{
		swapchainImageViews.emplace_back(vkDevice, swapchainImages[i], vkSwapchainFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
	}
}


template<typename Twindow>
VK_SwapChain<Twindow>::~VK_SwapChain()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_SwapChain()" << std::endl;
	}

	vkDestroySwapchainKHR(vkDevice, vkSwapchain, nullptr);
}


#endif // VK_SwapChain_CPP