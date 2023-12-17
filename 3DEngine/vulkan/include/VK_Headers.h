// VK_Headers.h
// The header to contain common external library headers for Vulkan 3D engine

#ifndef VK_Headers_H
#define VK_Headers_H

#define LibrarySDL
#ifdef LibrarySDL
#include "WindowSDL.h"
#endif // LibrarySDL

#include <vulkan/vulkan.h>

#include <iostream>
#include <string>
#include <vector>

// The class that stores all the basic parameters of the graphics
#include "Setup_Video.h"
#include "Main_AppInfo.h"

#ifdef NDEBUG
const bool enableValidationLayers = false;

#else
const bool enableValidationLayers = true;
#endif

#endif // VK_Headers_H