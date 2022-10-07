#pragma once
#include "../utils/dataprovider.h"

	// defines the camera modes
enum Camera_Mode {
	FREE_FLOAT,
	ISOMETRIC
};

struct GameSettings
{
	// screen size
	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;

	// camera perspective
	const Camera_Mode CAM_MODE;

	// debug options
	std::vector<float> POSTPROCESSING_KERNEL = DataProvider::noPostProcessing();
	bool ENABLE_POLYGONMODE = false;
	bool SHOW_NORMALS = false;
	bool SHOW_VERTICES = false;
	bool SHOW_COLLIDERS = false;


	// other options
};