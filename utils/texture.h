#pragma once

#include <glad/gl.h> 
#include "definitions.h"

#include <iostream>
#include <string>


class Texture {

public:
	Texture( GLenum _textureType );

	const unsigned int getID();

	// use/activate the texture
	void use(unsigned int _place);

	void setFilters( GLenum all );
	void setFilters( GLenum mag, GLenum min );

	void setWrap( GLenum all );
	void setWrap( GLenum s, GLenum t , GLenum r);



protected:
	GLuint id;
	GLenum textureType;
};
