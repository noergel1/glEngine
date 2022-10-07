#pragma once
#include "texture.h"

class Texture_CubeMap : public Texture {

public:
	// constructor reads and builds the texture
	Texture_CubeMap(std::vector<const char*> filepaths);
};