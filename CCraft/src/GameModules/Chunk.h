#pragma once
#include <vector>
#include "Block.h"

#define startingY 64.0f
#define baseGrassLayer 63.0f
#define baseDirtLayer 52.0f

namespace CCraft
{
	enum BlockID
	{
		AIR = 0, GRASS = 1, DIRT = 2, STONE = 3
	};

	class Chunk
	{
	public:
		float chunkCoordinateX, chunkCoordinateZ;
		std::vector<Block> blocks;
		bool active = false;
	public:
		Chunk(float chunkCoordinateX, float chunkCoordinateZ)
			: chunkCoordinateX(chunkCoordinateX), chunkCoordinateZ(chunkCoordinateZ)
		{
			blocks.reserve(128 * 64);
			
			float startingZ;
			float finalZ;
			float startingX;
			float finalX;

			calculateStartingFinalZ(startingZ, finalZ);
			calculateStartingFinalX(startingX, finalX);

			glm::mat4 translation;
			BlockID id;

			for (int y = startingY; y > 0; y--) //y layers to be generated
			{
				if (y > baseGrassLayer)
					id = BlockID::GRASS;
				else if (y > baseDirtLayer)
					id = BlockID::DIRT;
				else
					id = BlockID::STONE;

				for (float z = finalZ; z < startingZ; z++) //z rows per y layer to be generated
				{
					for (float x = startingX; x < finalX; x++) //x rows per z row to be generated
					{
						translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
						blocks.emplace_back(translation, id);
					}
				}
			}
		}

		void calculateStartingFinalZ(float& startingZ, float& finalZ)
		{
			if (chunkCoordinateZ == 0.0f)
				startingZ = 0.0f;
			else
				startingZ = chunkCoordinateZ * 8.0f;

			finalZ = startingZ - 8.0f;
		}

		void calculateStartingFinalX(float& startingX, float& finalX)
		{
			if (chunkCoordinateX == 0.0f)
				startingX = 0.0f;
			else
				startingX = chunkCoordinateX * 8.0f;

			finalX = startingX + 8.0f;
		}

	};
}