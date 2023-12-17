// VK_Queues.h

#ifndef VK_Queues_H
#define  VK_Queues_H

#include "VK_Headers.h"

struct VK_Queues
{
	VkQueue presentQueue;
	VkQueue graphicsQueue;
	VkQueue transferQueue;
};
#endif // VK_Queues_H
