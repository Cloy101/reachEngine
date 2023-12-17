// VK_ValidLayers.h

#ifndef VK_ValidLayers_H
#define VK_ValidLayers_H

#include "VK_Headers.h"

static const std::vector<const char*> VALIDATION_LAYERS = { "VK_LAYER_KHRONOS_validation" };

class VK_ValidLayers
{
private:
	std::vector<VkLayerProperties> availableLayers;

	bool checkValidationLayerSupport();

public:
	VK_ValidLayers();
		
	VK_ValidLayers& operator=(const VK_ValidLayers& vvl);

	~VK_ValidLayers();
};


#endif // VK_ValidLayers_H
