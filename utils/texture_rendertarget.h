#pragma once
#include "texture.h"

enum class TextureData {
	RGB,
	RGBA,
	DEPTH,
	STENCIL
};

class Texture_Rendertarget : public Texture {

public:
	// constructor for framebuffers -> NULL as data
	Texture_Rendertarget(unsigned int _width, unsigned int _height, TextureData _textureData);
};