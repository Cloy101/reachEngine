// VK_Instance.h

#ifndef VK_Instance_H
#define VK_Instance_H

#include "VK_Headers.h"
#include "VK_ValidLayers.h"
#include "VK_DebugMessenger.h"

class VK_Instance
{
private:
	VkInstance vkInstanse;

public:
	// Constructor of VK_Instance
	VK_Instance(std::vector<const char*> VkExtensions);

	VkInstance get_vkInstanse() { return vkInstanse; }

	// Function to create VkInstance via which communication between the application and the GPU takes place
	void createVkInstance(std::vector<const char*> VkExtensions);


	//  Destructor of a class VK_Instance
	~VK_Instance();


};

#endif // VK_Instance_H