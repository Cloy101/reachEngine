// VK_ImageView.cpp

#ifndef VK_ImageView_CPP
#define VK_ImageView_CPP

#include "VK_ImageView.h"


VK_ImageView::VK_ImageView() 
{

#ifndef NDEBUG
	std::cout << "VK_ImageView() default" <<std::endl;
#endif // !NDEBUG

	vkImageView = VK_NULL_HANDLE;
	vkDevice = VK_NULL_HANDLE;

}

VK_ImageView::VK_ImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels)
{

#ifndef NDEBUG
	std::cout << "VK_ImageView()" << std::endl;
#endif // !NDEBUG

	createImageView(device, image, format, aspectFlags, mipLevels);
	this->vkDevice = device;
}


void VK_ImageView::createImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels)
{
	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = aspectFlags;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = mipLevels;

	if (vkCreateImageView(device, &viewInfo, nullptr, &vkImageView) != VK_SUCCESS)
	{
		throw std::runtime_error("ERROR::VK_ImageView()::createImageView()::Failed to create texture image view");
	}
}


VK_ImageView::VK_ImageView(VK_ImageView&& moved) noexcept
{
	vkImageView = moved.vkImageView;
	vkDevice = moved.vkDevice;


	moved.vkImageView = VK_NULL_HANDLE;
	moved.vkDevice = VK_NULL_HANDLE;

}


VK_ImageView& VK_ImageView::operator=(VK_ImageView&& moved) noexcept
{
	if (&moved != this)
	{
		vkImageView = moved.vkImageView;
		vkDevice = moved.vkDevice;

		moved.vkImageView = VK_NULL_HANDLE;
		moved.vkDevice = VK_NULL_HANDLE;
	}
	return *this;
}

VK_ImageView::~VK_ImageView()
{
	if (enableValidationLayers)
	{
		if (vkDevice != VK_NULL_HANDLE && vkImageView != VK_NULL_HANDLE)
		{
			std::cout << "~VK_ImageView() with vkDestroyImageView" << std::endl;
		}
		else
		{
			std::cout << "~VK_ImageView()" << std::endl;
		}
	}
	
	if (vkDevice != VK_NULL_HANDLE && vkImageView !=VK_NULL_HANDLE)
	{
		vkDestroyImageView(vkDevice, vkImageView, nullptr);
	}
}

#endif // VK_ImageView_CPP