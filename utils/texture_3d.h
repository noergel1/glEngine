#pragma once
#include "texture.h"

class Texture_3D : public Texture {

public:

	Texture_3D();

	// constructor reads and builds the texture
	Texture_3D( const char* filepath, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT, GLenum wrapR = GL_REPEAT,  GLenum filterMag = GL_LINEAR, GLenum filterMin = GL_LINEAR );
	Texture_3D( unsigned int _width, unsigned int _height, unsigned int _depth, GLenum _colorMode, GLenum _wrapS = GL_REPEAT, GLenum _wrapT = GL_REPEAT, GLenum _wrapR = GL_REPEAT, GLenum _filterMag = GL_LINEAR, GLenum _filterMin = GL_LINEAR );
};