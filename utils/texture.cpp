#include "texture.h"

Texture::Texture( GLenum _textureType )
	:textureType(_textureType)
{
}

const unsigned int Texture::getID() {
	return id;
}

void Texture::use( unsigned int _place ) {
	glActiveTexture(GL_TEXTURE0 + _place);
	glBindTexture( textureType, id );
}

void Texture::setFilters( GLenum all ) {
	setFilters( all, all );
}

void Texture::setFilters( GLenum mag, GLenum min ) {
	glBindTexture( textureType, id );

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, mag);

	glBindTexture( textureType, 0 );
}

void Texture::setWrap( GLenum all ) {
	setWrap( all, all, all );
}

void Texture::setWrap( GLenum s, GLenum t, GLenum r ) {
	glBindTexture( textureType, id );

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, r);
	if(textureType == GL_TEXTURE_CUBE_MAP) glTexParameteri(textureType, GL_TEXTURE_WRAP_R, t);

	glBindTexture( textureType, 0 );
}
