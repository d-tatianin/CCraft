#pragma once
#include "Chunk.h"
#include "../logger/Logger.h"

namespace CCraft
{
	class ChunkController
	{
	public:
		std::vector<Chunk> chunks;
		int drawDistance;
	private:
		glm::mat4* blocks;
		Logger logger;
		int maximumBlocks;
		unsigned int instanceBuffer;
		int usedBlocks;
	public:
		ChunkController(int drawDistance);
		~ChunkController();
		void draw();
		void initBlockArray();
		void updateCoordinates();
		void bind();
	private:
		int calculateSize(int dd);
	};

}

