#include "texture_rendertarget.h"

Texture_Rendertarget::Texture_Rendertarget(unsigned int _width, unsigned int _height, TextureData _textureType)
	:Texture(GL_TEXTURE_2D)
{
	int colorType = 0;
	int dataType = 0;
	int dataFormat = 0;
	switch (_textureType) {
		case TextureData::RGB:
		{
			colorType = GL_RGB;
			dataFormat = GL_RGB;
			dataType = GL_UNSIGNED_BYTE;
			break;
		}
		case TextureData::RGBA:
		{
			colorType = GL_RGBA;
			dataFormat = GL_RGBA;
			dataType = GL_UNSIGNED_BYTE;
			break;
		}
		case TextureData::DEPTH:
		{
			colorType = GL_DEPTH_COMPONENT;
			dataFormat = GL_DEPTH_COMPONENT32;
			dataType = GL_UNSIGNED_SHORT;
			break;
		}
	}


	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// NULL as data
	glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, _width, _height, 0, colorType, dataType, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);
}