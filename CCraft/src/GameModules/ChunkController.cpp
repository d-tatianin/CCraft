#include "ChunkController.h"

namespace CCraft
{
	ChunkController::ChunkController(int drawDistance)
		: drawDistance(drawDistance), blocks(new glm::mat4[calculateSize(drawDistance)]), logger("ChunkController")
	{
		chunks.emplace_back(0.0f, 0.0f, Layer::Direction::FORWARD);
		initBlockArray();
		updateCoordinates();
	}

	void ChunkController::draw()
	{	
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, usedBlocks);
	}

	void ChunkController::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
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
		for (int i(0); i < maximumBlocks - 1; i++)
			blocks[i] = glm::mat4(1.0f);
		glGenBuffers(1, &instanceBuffer);
	}

	void ChunkController::updateCoordinates()
	{
		int i = 0;
		for (Chunk chnk : chunks)
		{
			for (Layer lyr : chnk.layers)
			{
				for (Block blk : lyr.blocks)
				{
					blocks[i] = blk.coordinates;
					++i;
					//has to be reset at some point/reworked
					++usedBlocks;
				}
			}	
		}
		glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, usedBlocks * sizeof(glm::mat4), blocks, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	ChunkController::~ChunkController()
	{
		delete[] blocks;
		glDeleteBuffers(1, &instanceBuffer);
	}
}




