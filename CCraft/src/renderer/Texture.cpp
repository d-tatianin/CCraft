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
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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


