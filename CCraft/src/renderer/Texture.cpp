#include "Texture.h"
#include <sstream>

namespace CCraft
{
	Texture::Texture(const char* path)
		:logger("TEXTURE")
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::stringstream ss;
			ss << "FAILED TO LOAD TEXTURE AT " << path;
			logger.log(ss.str().c_str(), Logger::level::FATAL);
		}
		stbi_image_free(data);
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
}


