// Setup_Video.cpp

#ifndef SETUP_VIDEO_CPP
#define SETUP_VIDEO_CPP

#include "Setup_Video.h"

Setup_Video::Setup_Video()
{
#ifndef NDEBUG
	std::cout << "Setup_Video()" << std::endl;
#endif // !NDEBUG

	set_screenResolution(Resolution::FHD);
}


void Setup_Video::set_screenResolution(Resolution resolution)
{
	switch (resolution)
	{
	case Resolution::WXGA:
		screenWidth = 1280;
		screenHeight = 720;
		break;

	case Resolution::HDp:
		screenWidth = 1600;
		screenHeight = 900;
		break;

	case Resolution::FHD:
		screenWidth = 1920;
		screenHeight = 1080;
		break;

	case Resolution::QHD:
		screenWidth = 2560;
		screenHeight = 1440;
		break;

	case Resolution::UHD:
		screenWidth = 3840;
		screenHeight = 2160;
		break;
		
	default:
		throw std::runtime_error("ERROR: Setup_Video::set_screenResolution()::Wrong resolution of the screen");
		break;
	}
}


Setup_Video::~Setup_Video()
{

}


#endif // !SETUP_VIDEO_CPP