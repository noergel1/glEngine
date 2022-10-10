#include "texture_3d.h"

Texture_3D::Texture_3D() 
	:Texture(GL_TEXTURE_3D)
{

}

	// constructor reads and builds the texture
Texture_3D::Texture_3D( const char* filepath, GLenum _wrapS, GLenum _wrapT, GLenum _wrapR, GLenum _filterMag, GLenum _filterMin ) 
	:Texture(GL_TEXTURE_3D)
{

}

	// constructor reads and builds the texture
Texture_3D::Texture_3D( unsigned int _width, unsigned int _height, unsigned int _depth, GLenum _colorMode, GLenum _wrapS, GLenum _wrapT, GLenum _wrapR, GLenum _filterMag, GLenum _filterMin ) 
	:Texture(GL_TEXTURE_3D)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_3D, id);

	glTexImage3D(GL_TEXTURE_3D, 0, _colorMode, _width, _height, _depth, 0, _colorMode, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, _wrapS);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, _wrapT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, _wrapR);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, _filterMin);
	glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, _filterMag );
	glGenerateMipmap(GL_TEXTURE_3D);

	glBindTexture(GL_TEXTURE_3D, 0);
}
