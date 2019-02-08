#include "ChunkController.h"

namespace CCraft
{
	ChunkController::ChunkController()
	{
		chunks.emplace_back(0.0f, 0.0f, Layer::Direction::FORWARD);
	}

	void ChunkController::draw()
	{
		for (Chunk chnk : chunks)
			chnk.draw();
	}
}




