#include "texture_2d.h"

#include "../utils/stb_image.h"

Texture_2D::Texture_2D()
	:Texture( GL_TEXTURE_2D ) 
{
		
}


Texture_2D::Texture_2D(const char* filepath, GLenum wrapS, GLenum wrapR, GLenum filterMag, GLenum filterMin)
	:Texture(GL_TEXTURE_2D)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum colorMode;
		switch (nrChannels) {
			case 1:
				colorMode = GL_RED;
				break;
			case 3:
				colorMode = GL_RGB;
				break;
			case 4:
				colorMode = GL_RGBA;
				break;
			default: 
				std::cout << "Unexpected texture nrChannels: " << nrChannels << " for " << filepath << "\n";
				colorMode = GL_RGB;
		};

		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag );
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture %s\n", filepath);
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

