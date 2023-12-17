// ReachEngineMain.cpp

#include "Main_ReachEngine.h"


//#include <SDL.h>
//#include <vulkan/vulkan.h>
//#include <SDL_vulkan.h>
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtx/hash.hpp>
//#include <stb_image.h>
//#include <tiny_obj_loader.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION


int SDL_main( int argc, char* argv[] )
{
    try
    {
		VK_Application vkApplication;
    }
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;

	}

    return 0;
}

