// VK_RenderPass.h

#ifndef VK_RenderPass_H
#define VK_RenderPass_H

#include "VK_Headers.h"

class VK_RenderPass
{
private:
	VkRenderPass vkRenderPass;
	VkDevice device;

public:
	VK_RenderPass(VkDevice device, VkFormat swapchainFormat, VkFormat depthFormat);

	VkRenderPass get_vkRenderPass() { return vkRenderPass; }

	~VK_RenderPass();
private:
	// Function to create the Vulkan redrer pass
	void createRenderPass(VkDevice device, VkFormat swapchainFormat, VkFormat depthFormat);

};

#endif // VK_RenderPass_H