// VK_RenderPass.cpp

#ifndef VK_RenderPass_CPP
#define VK_RenderPass_CPP

#include "VK_RenderPass.h"

VK_RenderPass::VK_RenderPass(VkDevice device, VkFormat swapchainFormat, VkFormat depthFormat)
{
 #ifndef NDEBUG
		std::cout << "VK_RenderPass()" << std::endl;
 #endif // !NDEBUG

		createRenderPass(device, swapchainFormat, depthFormat);
		this->device = device;
}
 

void VK_RenderPass::createRenderPass(VkDevice device, VkFormat swapchainFormat, VkFormat depthFormat)
{
	// Creating the Color Attachment
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = swapchainFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	/// the instruction what to do with the Attachment before the rendering and after the last one
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	/// the instruction what to do with the Stencil before the rendering and after the last one
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	/// the instruction what form the Attachment Layout use for the final image 
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	//
	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	//
	VkAttachmentDescription depthAttachment{};
	//depthAttachment.format = findDepthFormat();

	depthAttachment.format = depthFormat;
	depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	/// the instruction what form the Attachment Layout use for the final image 
	depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	//
	VkAttachmentReference depthAttachmentRef{};
	depthAttachmentRef.attachment = 1;
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	//
	VkSubpassDescription subPass{};
	subPass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subPass.colorAttachmentCount = 1;
	subPass.pColorAttachments = &colorAttachmentRef;
	subPass.pDepthStencilAttachment = &depthAttachmentRef;

	// Pointing to the dependency of Subpass
	VkSubpassDependency dependency{};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	/// Describing the operation to be waited for and the last stages in which they are performed
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.srcAccessMask = 0;
	/// This settings prevent to send the data during we allow this ( when we want to write the color into the buffer )
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

	std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
	//
	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
	renderPassInfo.pAttachments = attachments.data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subPass;
	// Pointing to the array of the dependencies
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &vkRenderPass) != VK_SUCCESS)
	{
		throw std::runtime_error("ERROR::VK_RenderPass::createRenderPass()::Failed to create the Render Pass");
	}
}


VK_RenderPass::~VK_RenderPass()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_RenderPass()" << std::endl;
	}

	vkDestroyRenderPass(device, vkRenderPass, nullptr);
}


#endif // VK_RenderPass_CPP