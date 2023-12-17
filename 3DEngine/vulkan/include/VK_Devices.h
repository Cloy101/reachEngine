// VK_Devices.h

#ifndef VK_Devices_H
#define VK_Devices_H

#include "VK_Headers.h"
#include "VK_QueueFamilies.h"
#include "VK_SwapChainSupportDetails.h"
#include "VK_Extensions.h"
#include "VK_Queues.h"
#include "VK_ValidLayers.h"
#include <map>
#include <set>

class VK_Devices
{
private:
	VkPhysicalDevice gpu;
	std::vector<VkPhysicalDevice> gpuList;
	VkPhysicalDeviceProperties gpuProperties;
	VkPhysicalDeviceFeatures gpuFeatures;
	std::multimap<int, VkPhysicalDevice> gpuRating;

	VkDevice vkDevice;

public:
	// Constructor of VK_Device
	VK_Devices(VkInstance vkInstance, VkSurfaceKHR vkSurface, VK_Queues* vkQueues);

	VkPhysicalDevice get_gpu() { return gpu; }
	VkDevice get_vkDevice() { return vkDevice; }

	~VK_Devices();

private:
	// Function to pick the most suitable GPU
	void pickGPU(VkInstance vkInstance, VkSurfaceKHR vkSurface);
	// Function to check suitability of the GPU
	bool isGPUSuitable(VkPhysicalDevice gpu, VkSurfaceKHR vkSurface);
	// Function to rate the suitability of available GPUs
	int rateGPUSuitability();
	// Function to create the Vulkan logical device
	void createVkDevice(VkPhysicalDevice gpu, VkSurfaceKHR vkSurface, VK_Queues* vkQueues);
	// Function to set the features pf logical device
	VkPhysicalDeviceFeatures setVkDeviceFeatures(VkPhysicalDeviceFeatures gpuFeatures);
};

#endif // VK_Devices_H