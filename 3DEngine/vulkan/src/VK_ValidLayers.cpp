// VK_ValidLayers.cpp

#ifndef VK_ValidLayers_CPP
#define VK_ValidLayers_CPP

#include "VK_ValidLayers.h"

VK_ValidLayers::VK_ValidLayers()
{
#ifndef NDEBUG
	std::cout << "VK_ValidLayers()" << std::endl;
#endif // !NDEBUG
	
	if (!checkValidationLayerSupport())
	{
		throw std::runtime_error("ERROR::VK_Instance::createVkInstance()::Validation layers requested, but not available");
	}
}


bool VK_ValidLayers::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	VkLayerProperties temp;
	for (uint32_t i{}; i < layerCount; ++i)
	{
		availableLayers.emplace_back(temp);
	}

	// This function enumerates supported Validation layers and fill the array with structures VkLayerProperties
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	// Checking the existing of VK_LAYER_KHRONOS_validation in the Available Layers
	for (const char* layerName : VALIDATION_LAYERS)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}
	return true;
}


VK_ValidLayers& VK_ValidLayers::operator=(const VK_ValidLayers& vvl)
{
	if (&vvl != this)
	{
		this->availableLayers = vvl.availableLayers;
	}

	return *this;
}


VK_ValidLayers::~VK_ValidLayers()
{
	if (enableValidationLayers)
	{
		std::cout << "~VK_ValidLayers()" << std::endl;
	}
}

#endif // VK_ValidLayers_CPP
