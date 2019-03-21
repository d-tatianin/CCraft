#include "ChunkController.h"

namespace CCraft
{
	std::vector<Chunk> ChunkController::chunks;
	bool ChunkController::blocksChanged;

	ChunkController::ChunkController(int drawDistance, glm::vec3& playerCoordinates)
		: drawDistance(drawDistance), playerCoordinates(playerCoordinates), grassBlocks(new glm::mat4[calculateSize(drawDistance)]),
		dirtBlocks(new glm::mat4[calculateSize(drawDistance)]), stoneBlocks(new glm::mat4[calculateSize(drawDistance)]), logger("ChunkController"),
		grassBlockTex("res/textures/grass.png"), dirtBlockTex("res/textures/dirt.png"), stoneBlockTex("res/textures/stone.png")
	{
		blocksChanged = false;
		generateInitialChunks();
		initBlockArray();
		updateCoordinates();
	}

	void ChunkController::generateInitialChunks()
	{
		if (drawDistance == 0)
		{
			chunks.emplace_back(0.0f, 0.0f);
			chunks[0].active = true;
		}
		else
		{
			chunks.emplace_back(0.0f, 0.0f);

			for (float i = drawDistance; i > 0; i--)
			{
				chunks.emplace_back(0.0f - i, 0.0f);
				for (float j = drawDistance; j > 0; j--)
				{
					chunks.emplace_back(0.0f - i, 0.0f + j);
					chunks.emplace_back(0.0f - i, 0.0f - j);
				}

				chunks.emplace_back(0.0f + i, 0.0f);
				for (float j = drawDistance; j > 0; j--)
				{
					chunks.emplace_back(0.0f + i, 0.0f + j);
					chunks.emplace_back(0.0f + i, 0.0f - j);
				}
				chunks.emplace_back(0.0f, 0.0f - i);
				chunks.emplace_back(0.0f, 0.0f + i);
			}
			for (int i = 0; i < chunks.size(); i++)
			{
				chunks[i].active = true;
			}
		}
	}

	void ChunkController::generateAdditionalChunks(float x, float z)
	{
		for (Chunk& chnk : chunks)
			chnk.active = false;

		grassIndex = 0;
		dirtIndex = 0;
		stoneIndex = 0;


		if (drawDistance == 0)
		{
			auto itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x && c.chunkCoordinateZ == z) return true; else return false; });
			if (itr == chunks.end())
			{
				chunks.emplace_back(x, z);
				chunks[chunks.size() - 1].active = true;
			}
			else
				itr->active = true;
		}
		else
		{
			auto itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x && c.chunkCoordinateZ == z) return true; else return false; });
			if(itr == chunks.end())
			{
				chunks.emplace_back(x, z);
				chunks[chunks.size() - 1].active = true;
			}
			else
				itr->active = true;
			

			for (float i = drawDistance; i > 0; i--)
			{
				itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x - i && c.chunkCoordinateZ == z) return true; else return false; });
				if (itr == chunks.end())
				{
					chunks.emplace_back(x - i, z);
					chunks[chunks.size() - 1].active = true;
				}
				else
					itr->active = true;

				for (float j = drawDistance; j > 0; j--)
				{
					itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x - i && c.chunkCoordinateZ == z + j) return true; else return false; });
					if (itr == chunks.end())
					{
						chunks.emplace_back(x - i, z + j);
						chunks[chunks.size() - 1].active = true;
					}
					else
						itr->active = true;

					itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x - i && c.chunkCoordinateZ == z - j) return true; else return false; });
					if (itr == chunks.end())
					{
						chunks.emplace_back(x - i, z - j);
						chunks[chunks.size() - 1].active = true;
					}
					else
						itr->active = true;
				}

				itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x + i && c.chunkCoordinateZ == z) return true; else return false; });
				if (itr == chunks.end())
				{
					chunks.emplace_back(x + i, z);
					chunks[chunks.size() - 1].active = true;
				}
				else
					itr->active = true;

				for (float j = drawDistance; j > 0; j--)
				{
					itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x + i && c.chunkCoordinateZ == z + j) return true; else return false; });
					if (itr == chunks.end())
					{
						chunks.emplace_back(x + i, z + j);
						chunks[chunks.size() - 1].active = true;
					}
					else
						itr->active = true;

					itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x + i && c.chunkCoordinateZ == z - j) return true; else return false; });
					if (itr == chunks.end())
					{
						chunks.emplace_back(x + i, z - j);
						chunks[chunks.size() - 1].active = true;
					}
					else
						itr->active = true;
				}

				itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x && c.chunkCoordinateZ == z - i) return true; else return false; });
				if (itr == chunks.end())
				{
					chunks.emplace_back(x, z - i);
					chunks[chunks.size() - 1].active = true;
				}
				else
					itr->active = true;

				itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == x && c.chunkCoordinateZ == z + i) return true; else return false; });
				if (itr == chunks.end())
				{
					chunks.emplace_back(x, z + i);
					chunks[chunks.size() - 1].active = true;
				}
				else
					itr->active = true;
			}
		}
		updateCoordinates();
	}

	void ChunkController::draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, grassInstanceBuffer);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		grassBlockTex.bind();
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, grassIndex);

		glBindBuffer(GL_ARRAY_BUFFER, dirtInstanceBuffer);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		dirtBlockTex.bind();
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, dirtIndex);

		glBindBuffer(GL_ARRAY_BUFFER, stoneInstanceBuffer);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		stoneBlockTex.bind();
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, stoneIndex);
	}

	int ChunkController::calculateSize(int dd)
	{
		int size = 8192;

		if (dd > 0)
		{
			while (dd > 0)
			{
				size += dd * 8192 * 8;
				--dd;
			}
			maximumBlocks = size;
			return size;
		}
		else
		{
			maximumBlocks = 8192;
			return 8192;
		}	
	}

	void ChunkController::initBlockArray()
	{
		glGenBuffers(1, &grassInstanceBuffer);
		glGenBuffers(1, &dirtInstanceBuffer);
		glGenBuffers(1, &stoneInstanceBuffer);
	}

	void ChunkController::updateCoordinates()
	{
		for (Chunk& chnk : chunks)
		{
			if (chnk.active)
			{
				for (Block& blk : chnk.blocks)
				{
					if (blk.id == 1)
					{
						grassBlocks[grassIndex] = blk.coordinates;
						grassIndex++;
					}
					else if (blk.id == 2)
					{
						dirtBlocks[dirtIndex] = blk.coordinates;
						dirtIndex++;
					}
					else if (blk.id == 3)
					{
						stoneBlocks[stoneIndex] = blk.coordinates;
						stoneIndex++;
					}
				}
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, grassInstanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, (grassIndex + 1) * sizeof(glm::mat4), grassBlocks, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, dirtInstanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, (dirtIndex + 1) * sizeof(glm::mat4), dirtBlocks, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, stoneInstanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, (stoneIndex + 1) * sizeof(glm::mat4), stoneBlocks, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void ChunkController::updateActiveChunks()
	{
		static float oldChunkX = 0.0f;
		static float oldChunkZ = 0.0f;

		float currentChunkX = playerCoordinates.x / 8.0f;
		float currentChunkZ = playerCoordinates.z / 8.0f;

		currentChunkX = floor(currentChunkX);
		currentChunkZ = ceil(currentChunkZ);

		if (currentChunkX != oldChunkX || currentChunkZ != oldChunkZ)
		{
			oldChunkX = currentChunkX;
			oldChunkZ = currentChunkZ;
			generateAdditionalChunks(oldChunkX, oldChunkZ);
			blocksChanged = false;
		}
		else if (blocksChanged)
		{
			blocksChanged = false;
			grassIndex = 0;
			dirtIndex = 0;
			stoneIndex = 0;
			updateCoordinates();
		}
			
	}

	void ChunkController::removeBlock(glm::vec3& blockCoordinates)
	{
		float chunkX = floor(blockCoordinates.x / 8.0f);
		float chunkZ = ceil(blockCoordinates.z / 8.0f);
		auto itr = std::find_if(chunks.begin(), chunks.end(), [&](Chunk& c) {if (c.chunkCoordinateX == chunkX && c.chunkCoordinateZ == chunkZ) return true; else return false; });
		if (itr != chunks.end())
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), blockCoordinates);
			auto blockItr = std::find_if(itr->blocks.begin(), itr->blocks.end(), [&](Block& b) {if (b.coordinates == translation) return true; else return false; });
			if (blockItr != itr->blocks.end())
				itr->blocks.erase(blockItr);
		}
		blocksChanged = true;
	}

	ChunkController::~ChunkController()
	{
		delete[] grassBlocks;
		delete[] dirtBlocks;
		delete[] stoneBlocks;
		
		glDeleteBuffers(1, &grassInstanceBuffer);
		glDeleteBuffers(1, &dirtInstanceBuffer);
		glDeleteBuffers(1, &stoneInstanceBuffer);
	}
}




