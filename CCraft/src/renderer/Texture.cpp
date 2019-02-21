#include "Texture.h"
#include <sstream>

namespace CCraft
{
	Texture::Texture(const char* path)
		:logger("TEXTURE")
	{
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;
			else
				format = GL_RGB;
				
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::stringstream ss;
			ss << "FAILED TO LOAD TEXTURE AT " << path;
			logger.log(ss.str().c_str(), Logger::level::FATAL);
		}
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
}


