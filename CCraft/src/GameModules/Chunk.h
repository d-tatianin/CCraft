#pragma once
#include <vector>
#include "Block.h"
#include "Layer.h"
namespace CCraft
{
	enum BlockID
	{
		AIR = 0, GRASS = 1, DIRT = 2, STONE = 3
	};

	class Chunk
	{
	private:
		float baseY = 64.0f;
		float baseGrassLayer = 63.0f;
		float baseDirtLayer = 52.0f;
		std::vector<Layer> layers;
	public:
		Chunk(float x, float z, Layer::Direction direction)
		{
			layers.reserve(128);
			generateLayers(x, z, direction);
		}

		void generateLayers(float x, float z, Layer::Direction direction)
		{
			float y = baseY;

			for (int i(0); i < 64; i++)
			{
				if (y > 63.0f)
					layers.emplace_back(x, y, z, direction, (int)BlockID::GRASS);
				else if (y > 52.0f)
					layers.emplace_back(x, y, z, direction, (int)BlockID::DIRT);
				else
					layers.emplace_back(x, y, z, direction, (int)BlockID::STONE);
				y--;
			}
		}

		void draw()
		{
			for (Layer layr : layers)
				layr.draw();
		}
	};
}