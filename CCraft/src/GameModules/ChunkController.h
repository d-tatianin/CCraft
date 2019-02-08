#pragma once
#include "Chunk.h"

namespace CCraft
{
	class ChunkController
	{
	public:
		std::vector<Chunk> chunks;
	public:
		ChunkController();
		void draw();
	};

}

