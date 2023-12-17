// Setup_Video.h

#ifndef SETUP_VIDEO_H
#define SETUP_VIDEO_H

#include <stdexcept>
#include <iostream>

enum class Resolution { WXGA, HDp, FHD, QHD, UHD };

class Setup_Video
{
public:
	// Constructor of the class Setup_Video
	Setup_Video();

	// Function to set up the screen resolution
	// available resolution: WXGA(1280x720)=0, HDp(1600x900)=1, FHD(1920x1080)=2, QHD(2560x1440)=3, UHD(3840x2160)=4
	void set_screenResolution(Resolution resolution);
	
	// Getters of the Screen Resolution
	uint32_t get_screenWidth() { return screenWidth; }
	uint32_t get_screenHeight() { return screenHeight; }

	~Setup_Video();

private:

	uint32_t screenWidth;
	uint32_t screenHeight;
};

#endif // SETUP_VIDEO_H