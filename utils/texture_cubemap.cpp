#include "texture_cubemap.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"

Texture_CubeMap::Texture_CubeMap(std::vector<const char*> filepaths)
	:Texture(GL_TEXTURE_CUBE_MAP)
{
	if (filepaths.size() < 6)
	{
		assert("Cubemap contains fewer than 6 textures!");
	}

	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < filepaths.size(); i++)
	{
		unsigned char* data = stbi_load(filepaths[i], &width, &height, &nrChannels, 0);

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
				std::cout << "Unexpected texture nrChannels: " << nrChannels << " for " << filepaths[i] << "\n";
				colorMode = GL_RGB;
		};

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << filepaths[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}