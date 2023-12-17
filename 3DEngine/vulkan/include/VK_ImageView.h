// VK_ImageView.h

#ifndef VK_ImageView_H
#define VK_ImageView_H

#include "VK_Headers.h"

class VK_ImageView
{
private:
	VkImageView vkImageView;
	VkDevice vkDevice;

public:

	VK_ImageView();
	VK_ImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

	VkImageView get_vkImageView() { return vkImageView; }
	// Copy constructor
	VK_ImageView(VK_ImageView& other) = delete;
	VK_ImageView& operator=(const VK_ImageView& other) noexcept = delete;
	//VK_ImageView& operator=(const VK_ImageView& other) noexcept;
	VK_ImageView(VK_ImageView&& moved) noexcept;
	VK_ImageView& operator=(VK_ImageView&& moved) noexcept;


	~VK_ImageView();
private:
	// Function to create the Vulkan Image View
	void createImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

};



#endif // VK_ImageView_H