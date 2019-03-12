#pragma once
#include <vector>
#include "Block.h"

namespace CCraft
{
	struct Layer
	{
		enum Direction
		{
			FORWARD = 0, BACKWARD = 1, LEFT = 2, RIGHT = 3
		};

	public:
		std::vector<Block> blocks;
	public:
		Layer(float x, float y, float z, Direction direction, int id)
		{
			blocks.reserve(64);
			generateLayer(x, y, z, direction, id);
		}


		void generateLayer(float x, float y, float z, Direction direction, int id)
		{
			glm::mat4 translation = glm::mat4(1.0f);

			if (direction == Direction::FORWARD)
			{
				for (int i(0); i < 8; i++)
				{
					for (int j(0); j < 8; j++)
					{
						translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
						blocks.emplace_back(translation, id);
						x++;
					}
					x -= 8;
					z--;
				}
			}

			else if (direction == Direction::BACKWARD)
			{
				for (int i(0); i < 8; i++)
				{
					for (int j(0); j < 8; j++)
					{
						translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
						blocks.emplace_back(translation, id);
						x++;
					}
					x -= 8;
					z++;
				}
			}

			else if (direction == Direction::LEFT)
			{
				for (int i(0); i < 8; i++)
				{
					for (int j(0); j < 8; j++)
					{
						translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
						blocks.emplace_back(translation, id);
						x--;
					}
					x += 8;
					z++;
				}
			}

			else if (direction == Direction::RIGHT)
			{
				for (int i(0); i < 8; i++)
				{
					for (int j(0); j < 8; j++)
					{
						translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
						blocks.emplace_back(translation, id);
						x++;
					}
					x -= 8;
					z++;
				}
			}
		}
	};
}
