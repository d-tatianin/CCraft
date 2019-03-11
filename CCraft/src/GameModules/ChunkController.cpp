#include "ChunkController.h"

namespace CCraft
{
	ChunkController::ChunkController(int drawDistance)
		: drawDistance(drawDistance), grassBlocks(new glm::mat4[calculateSize(drawDistance)]),
		dirtBlocks(new glm::mat4[calculateSize(drawDistance)]), stoneBlocks(new glm::mat4[calculateSize(drawDistance)]), logger("ChunkController"),
		grassBlockTex("res/textures/grass.png"), dirtBlockTex("res/textures/dirt.png"), stoneBlockTex("res/textures/stone.png")
	{
		chunks.emplace_back(0.0f, 0.0f, Layer::Direction::FORWARD);
		initBlockArray();
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
			for (Layer& lyr : chnk.layers)
			{
				for (Block& blk : lyr.blocks)
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




