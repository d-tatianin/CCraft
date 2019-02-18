#pragma once
#include "glad/glad.h"
#include "../vendor/stb_image/stb_image.h"
#include "../logger/Logger.h"

namespace CCraft
{
	class Texture
	{
	private:
		Logger logger;
		unsigned int textureID;
		int width, height, nrChannels;
	public:
		Texture(const char* path);
		void bind();
	};

}

