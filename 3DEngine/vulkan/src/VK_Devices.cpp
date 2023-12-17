// VK_Devices.cpp

#ifndef VK_Devices_CPP
#define VK_Devices_CPP

#include "VK_Devices.h"

VK_Devices::VK_Devices(VkInstance vkInstance, VkSurfaceKHR vkSurface, VK_Queues* vkQueues)
{
#ifndef NDEBUG
	std::cout << "VK_Devices()" << std::endl;
#endif // !NDEBUG

	gpu = VK_NULL_HANDLE;
	pickGPU(vkInstance, vkSurface);
	createVkDevice(gpu, vkSurface, vkQueues);
}


void VK_Devices::pickGPU(VkInstance vkInstance, VkSurfaceKHR vkSurface)
{
	uint32_t gpuCount = 0;

	// Find the quantity of Devices that can support Vulkan API
	vkEnumeratePhysicalDevices(vkInstance, &gpuCount, nullptr);
	//// Initialization of std::vector<VkPhysicalDevice> devices by 0
	if (gpuCount == 0)
	{
		throw std::runtime_error("ERROR::VK_Devices::pickGPU()::Failed to find GPUs with Vulkan support");
		gpuList.emplace_back(gpu);
	}
	else
	{
		for (uint32_t i{}; i < gpuCount; i++)
		{
			gpuList.emplace_back(gpu);
		}
	}

	vkEnumeratePhysicalDevices(vkInstance, &gpuCount, gpuList.data());

	// Checking support for certain Vulkan features by an available devices
	for (const auto& gpuTemp : gpuList)
	{
		if (isGPUSuitable(gpuTemp, vkSurface))
		{
			gpu = gpuTemp;
			break;
		}
	}

	if (gpu == VK_NULL_HANDLE)
	{
		throw std::runtime_error("ERROR::VK_Devices::pickGPU()::Failed to find the GPU with specified ptoperties and features");
	}

	// Use an ordered map to automatically sort candidates by increasing score
	for (const auto& temp : gpuList)
	{
		int score = rateGPUSuitability();
		gpuRating.emplace(std::make_pair(score, temp));
	}

	// Check if the best candidate is suitable at all
	if (gpuRating.rbegin()->first > 0)
	{
		gpu = gpuRating.rbegin()->second;
	}
	else
	{
		throw std::runtime_error("ERROR::VK_Devices::pickGPU::Failed to find a GPU with needed rating");
	}
}


bool VK_Devices::isGPUSuitable(VkPhysicalDevice gpu, VkSurfaceKHR vkSurface)
{
	// get properties of GPU
	vkGetPhysicalDeviceProperties(gpu, &gpuProperties);
	if (enableValidationLayers)
	{
		std::cout << "===================================" << std::endl <<
			"GPU PROPERTIES" << std::endl <<
			"Device ID: " << gpuProperties.deviceID << std::endl <<
			"GPU name: " << gpuProperties.deviceName << std::endl <<
			"GPU type: " << gpuProperties.deviceType << std::endl <<
			"API Version: " << gpuProperties.apiVersion << std::endl <<
			"Driver version: " << gpuProperties.driverVersion << std::endl <<
			"Vendor: " << gpuProperties.vendorID << std::endl <<
			"===================================" << std::endl;
	}

	// get features of GPU
	vkGetPhysicalDeviceFeatures(gpu, &gpuFeatures);

	VK_QueueFamilies queueIndices = VK_QueueFamilies::findQueueFamilies(gpu, vkSurface);

	// Checking of capability the Physical Device supports the extensions for the SwapChain
	VK_Extensions vkExtensions;
	bool extensionsSupported = vkExtensions.checkDeviceExtensionSupport(gpu);
	bool swapChainAdequate = false;
	if (extensionsSupported)
	{
		VK_SwapChainSupportDetails swapChainSupport = VK_SwapChainSupportDetails::querySwapChainSupport(gpu, vkSurface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	VkPhysicalDeviceFeatures supportedFeatures;
	vkGetPhysicalDeviceFeatures(gpu, &supportedFeatures);

	return gpuProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && //
		gpuFeatures.geometryShader && //
		queueIndices.isComplete() && //
		extensionsSupported && // It's true when the Physical Device supports all necessary extensions for the SwapChain
		swapChainAdequate &&
		supportedFeatures.samplerAnisotropy; // It's true when formats and presentModes of the Physical Devices aren't empty
}


int VK_Devices::rateGPUSuitability()
{
	int score{};

	// Discrete GPUs have a significant performance advantage
	if (gpuProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
	{
		score += 1000;
	}

	// Maximum possible size of textures affects graphics quality
	score += gpuProperties.limits.maxImageDimension2D;

	// Application can't function without geometry shaders
	if (!gpuFeatures.geometryShader)
	{
		return 0;
	}

	return score;
}


void VK_Devices::createVkDevice(VkPhysicalDevice gpu, VkSurfaceKHR vkSurface, VK_Queues* vkQueues)
{
	// Searching for available indices of families of Physical Device
	VK_QueueFamilies indices = VK_QueueFamilies::findQueueFamilies(gpu, vkSurface);
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	float queuePriority = 1.0f;

	// Making the ordered list of Unique queue families indices
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value(), indices.transferFamily.value() };

	// Making structure with quantity of queues and information about that for each Queue families 
	for (auto temp : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = temp;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.emplace_back(queueCreateInfo);
	}
	// Creating the structure with information of features of the Physical device
	VkPhysicalDeviceFeatures deviceFeatures = setVkDeviceFeatures(gpuFeatures);

	// Creating the main structure with information for the Logical device
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pEnabledFeatures = &deviceFeatures;
	// Adding the information about an extension VK_KHR_swapchain to the logical device
	createInfo.enabledExtensionCount = static_cast<uint32_t>(DEVICE_EXTENSIONS.size());
	createInfo.ppEnabledExtensionNames = DEVICE_EXTENSIONS.data();

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
		createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	// Creating the Logical device
	if (vkCreateDevice(gpu, &createInfo, nullptr, &vkDevice) != VK_SUCCESS)
	{
		throw std::runtime_error("ERROR::Screen::createLogicalDevice()::Failed to create a logical device");
	}

	// Getting the Descriptor of the queues
	vkGetDeviceQueue(vkDevice, indices.graphicsFamily.value(), 0, &vkQueues->graphicsQueue);
	vkGetDeviceQueue(vkDevice, indices.presentFamily.value(), 0, &vkQueues->presentQueue);
	vkGetDeviceQueue(vkDevice, indices.transferFamily.value(), 0, &vkQueues->transferQueue);
}


VkPhysicalDeviceFeatures VK_Devices::setVkDeviceFeatures(VkPhysicalDeviceFeatures gpuFeatures)
{
	// Setting all the nessecary features for VkDevice
	VkPhysicalDeviceFeatures temp{};
	temp.samplerAnisotropy = VK_TRUE;
	// TODO 
	// temp.anotheFeature = VK_TRUE;
	
	// Check the supporting the desired feature by GPU
	bool areFeaturesSupported = true;

	// Compare bool variables
	const VkBool32* gpuFeaturesArray = reinterpret_cast<const VkBool32*>(&gpuFeatures);
	VkBool32* tempArray = reinterpret_cast<VkBool32*>(&temp);

	size_t numFeatures = sizeof(VkPhysicalDeviceFeatures) / sizeof(VkBool32);

	for (size_t i = 0; i < numFeatures; ++i)
	{
		if (tempArray[i]==VK_TRUE && gpuFeaturesArray[i]==VK_FALSE)
		{
			areFeaturesSupported = false;
			break;  // No need to continue checking if one feature is not supported
		}
	}

	if (areFeaturesSupported) return temp;
	else
	{
		throw std::runtime_error("ERROR::VK_Devices::setVkDeviceFeatures()::Some features isn't supported bu GPU");
	}
}


VK_Devices::~VK_Devices()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_Devices()" << std::endl;
	}
	vkDestroyDevice(vkDevice, nullptr);
}

#endif // VK_Devices_CPP