#pragma once
#include "Chunk.h"
#include "../logger/Logger.h"
#include "../renderer/Texture.h"
#include <algorithm>
#include <math.h>
namespace CCraft
{
	class ChunkController
	{
	public:
		static std::vector<Chunk> chunks;
		int drawDistance;
		glm::vec3& playerCoordinates;
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
		static bool blocksChanged;
	public:
		ChunkController(int drawDistance, glm::vec3& playerCoordinates);
		~ChunkController();
		void draw();
		void initBlockArray();
		void updateCoordinates();
		void updateActiveChunks();
		static void removeBlock(glm::vec3& blockCoordinates);
		static void placeBlock(glm::vec3& blockCoordinates);
	private:
		int calculateSize(int dd);
		void generateInitialChunks();
		void generateAdditionalChunks(float x, float z);
	};

}

