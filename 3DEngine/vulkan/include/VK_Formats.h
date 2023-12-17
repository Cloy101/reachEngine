// VK_Formats.h

#ifndef VK_Formats_H
#define VK_Formats_H

#include "VK_Headers.h"

class VK_Formats
{
private:
	VkFormat depthFormat;
	VkFormat colorFormat;

public:
	VK_Formats(VkPhysicalDevice gpu);

	~VK_Formats();
private:
	VkFormat findSupportedFormat(VkPhysicalDevice gpu, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat(VkPhysicalDevice gpu);

	void findColorFormat(VkPhysicalDevice gpu);

};

#endif // VK_Formats_H