// VK_Formats.cpp

#ifndef VK_Formats_CPP
#define VK_Formats_CPP

#include "VK_Formats.h"

VK_Formats::VK_Formats(VkPhysicalDevice gpu)
{
 #ifndef NDEBUG
		std::cout << "VK_Formats()" << std::endl;
 #endif // !NDEBUG


}

VkFormat VK_Formats::findSupportedFormat(VkPhysicalDevice gpu, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	for (VkFormat format : candidates)
	{
		VkFormatProperties formatProperties;
		vkGetPhysicalDeviceFormatProperties(gpu, format, &formatProperties);

		if (tiling == VK_IMAGE_TILING_LINEAR && (formatProperties.linearTilingFeatures & features) == features)
		{
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (formatProperties.optimalTilingFeatures & features) == features)
		{
			return format;
		}

		throw std::runtime_error("ERROR::VK_Formats::findSupportedFormat()::Failed ti find supported format");
	}
}


VkFormat VK_Formats::findDepthFormat(VkPhysicalDevice gpu)
{
	return findSupportedFormat(gpu,
		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}


void VK_Formats::findColorFormat(VkPhysicalDevice gpu)
{
	findSupportedFormat(gpu,
		{ VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R16G16B16A16_SFLOAT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT
	);
}

 
VK_Formats::~VK_Formats()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_Formats()" << std::endl;
	}
}

#endif // VK_Formats_CPP