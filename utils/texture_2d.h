#pragma once
#include "texture.h"

class Texture_2D : public Texture {

public:

	Texture_2D();

	// constructor reads and builds the texture
	Texture_2D( const char* filepath, GLenum wrapS = GL_REPEAT, GLenum wrapR = GL_REPEAT, GLenum filterMag = GL_LINEAR, GLenum filterMin = GL_LINEAR );
};
