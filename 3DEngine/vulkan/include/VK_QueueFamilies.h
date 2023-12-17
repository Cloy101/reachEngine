// VK_QueueFamilies.h

#ifndef VK_QueueFamilies_H
#define VK_QueueFamilies_H

#include "VK_Headers.h"
#include <optional>

struct VK_QueueFamilies
{
	// This Queue Family contains the queues of Graphics commands
	std::optional<uint32_t> graphicsFamily;

	// This Queue Family contains the queues of Present commands
	std::optional<uint32_t> presentFamily;

	// This Queue Family contains the queues of Transfer commands
	std::optional<uint32_t> transferFamily;

	// Function to check
	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value() && transferFamily.has_value();
	}

	// Function to find the Queue Family indices supported by GPU
	static VK_QueueFamilies findQueueFamilies(VkPhysicalDevice gpu, VkSurfaceKHR vkSurface)
	{
		VK_QueueFamilies indices;
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueFamilyCount, queueFamilies.data());

		// Checking the support of certain Family commands
		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			// Finding the support of the Family command for graphics
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) // VkQueueFlagBits
			{
				indices.graphicsFamily = i;
			}

			// Finding the support of the Family command for present
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(gpu, i, vkSurface, &presentSupport);
			if (presentSupport)
			{
				indices.presentFamily = i;
			}

			// Finding the support of the Transport commands for GPU
			if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) // VkQueueFlagBits
			{
				indices.transferFamily = i;
			}

			if (indices.isComplete())
			{
				return indices;
			}

			i++;
		}
	}
};

#endif // VK_QueueFamilies_H
