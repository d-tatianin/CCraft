#pragma once
#include "Chunk.h"
#include "../logger/Logger.h"
#include "../renderer/Texture.h"

namespace CCraft
{
	class ChunkController
	{
	public:
		std::vector<Chunk> chunks;
		int drawDistance;
	private:
		glm::mat4* grassBlocks;
		glm::mat4* dirtBlocks;
		glm::mat4* stoneBlocks;
		Logger logger;
		Texture grassBlockTex;
		Texture dirtBlockTex;
		Texture stoneBlockTex;
		int maximumBlocks;

		unsigned int grassInstanceBuffer;
		unsigned int dirtInstanceBuffer;
		unsigned int stoneInstanceBuffer;

		int grassIndex = 0;
		int dirtIndex = 0;
		int stoneIndex = 0;
	public:
		ChunkController(int drawDistance);
		~ChunkController();
		void draw();
		void initBlockArray();
		void updateCoordinates();
	private:
		int calculateSize(int dd);
	};

}

