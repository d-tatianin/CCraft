#include "CollisionDetection.h"
#include "ChunkController.h"
#define PlayerSize 0.3f //controls collision detection range.
#define BlockPlacementRange 5
namespace CCraft
{
	std::array<std::set<std::pair<float, float>>, WORLD_HEIGHT> CollisionDetection::collisionMap;

	void CollisionDetection::addCollisionElement(glm::vec3 coords)
	{
		collisionMap[(int)coords.y].insert(std::make_pair(coords.x, coords.z));
	}

	void CollisionDetection::removeCollisionElement(glm::vec3 coords)
	{
		collisionMap[(int)coords.y].erase(std::make_pair(coords.x, coords.z));
	}
	//should also test for the 4 blocks around the player: x+1 z-1, x-1 z-1, x+1 z+1, x-1 z+1.
	void CollisionDetection::testForCollision(glm::vec3 playerPosition, glm::vec3& directionVector, Camera_Movement direction, float velocity)
	{
		float blockX;
		float blockZ;
		float blockY;

		if (direction == FORWARD || direction == RIGHT)
		{
			playerPosition += directionVector * velocity;

			glm::vec3 tempoPlayerPositionX = playerPosition;
			glm::vec3 tempoPlayerPositionZ = playerPosition;
			
			if (directionVector.x < 0)
			{
				tempoPlayerPositionX.x -= PlayerSize;
				blockX = floor(tempoPlayerPositionX.x);
			}
			else
			{
				tempoPlayerPositionX.x += PlayerSize;
				blockX = floor(tempoPlayerPositionX.x);
			}
			
			if (tempoPlayerPositionX.y == round(tempoPlayerPositionX.y))
			{
				blockZ = floor(tempoPlayerPositionX.z);
				blockY = tempoPlayerPositionX.y;

				if (collisionMap[blockY - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 1].end())
				{
					directionVector.x = 0.0f;
				}
				if (collisionMap[blockY - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 2].end())
				{
					directionVector.x = 0.0f;
				}
			}
			else
			{
				blockZ = floor(tempoPlayerPositionX.z);
				blockY = ceil(tempoPlayerPositionX.y);

				if (collisionMap[blockY - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 1].end())
				{
					directionVector.x = 0.0f;
				}
				if (collisionMap[blockY - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 2].end())
				{
					directionVector.x = 0.0f;
				}
				if (collisionMap[blockY - 3].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 3].end())
				{
					directionVector.x = 0.0f;
				}
			}


			if (directionVector.z < 0.0f)
			{
				tempoPlayerPositionZ.z -= PlayerSize;
				blockZ = floor(tempoPlayerPositionZ.z);
			}
			else
			{
				tempoPlayerPositionZ.z += PlayerSize;
				blockZ = floor(tempoPlayerPositionZ.z);
			}

			if (tempoPlayerPositionZ.y == round(tempoPlayerPositionZ.y))
			{

				blockX = floor(tempoPlayerPositionZ.x);
				blockY = tempoPlayerPositionZ.y;

				if (collisionMap[blockY - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 1].end())
				{
					directionVector.z = 0.0f;
				}
				if (collisionMap[blockY - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 2].end())
				{
					directionVector.z = 0.0f;
				}
			}
			else
			{
				blockX = floor(tempoPlayerPositionZ.x);
				blockY = ceil(tempoPlayerPositionZ.y);

				if (collisionMap[blockY - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 1].end())
				{
					directionVector.z = 0.0f;
				}
				if (collisionMap[blockY - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 2].end())
				{
					directionVector.z = 0.0f;
				}
				if (collisionMap[blockY - 3].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 3].end())
				{
					directionVector.z = 0.0f;
				}
			}
		}
		
		if (direction == BACKWARD || direction == LEFT)
		{
			playerPosition -= directionVector * velocity;

			glm::vec3 tempoPlayerPositionX = playerPosition;
			glm::vec3 tempoPlayerPositionZ = playerPosition;

			if (directionVector.x > 0)
			{
				tempoPlayerPositionX.x -= PlayerSize;
				blockX = floor(tempoPlayerPositionX.x);
			}
			else
			{
				tempoPlayerPositionX.x += PlayerSize;
				blockX = floor(tempoPlayerPositionX.x);
			}

			if (tempoPlayerPositionX.y == round(tempoPlayerPositionX.y))
			{
				blockZ = floor(tempoPlayerPositionX.z);
				blockY = tempoPlayerPositionX.y;

				if (collisionMap[blockY - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 1].end())
				{
					directionVector.x = 0.0f;
				}
				if (collisionMap[blockY - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 2].end())
				{
					directionVector.x = 0.0f;
				}
			}
			else
			{
				blockZ = floor(tempoPlayerPositionX.z);
				blockY = ceil(tempoPlayerPositionX.y);

				if (collisionMap[blockY - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 1].end())
				{
					directionVector.x = 0.0f;
				}
				if (collisionMap[blockY - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 2].end())
				{
					directionVector.x = 0.0f;
				}
				if (collisionMap[blockY - 3].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 3].end())
				{
					directionVector.x = 0.0f;
				}
			}


			if (directionVector.z > 0.0f)
			{
				tempoPlayerPositionZ.z -= PlayerSize;
				blockZ = floor(tempoPlayerPositionZ.z);
			}
			else
			{
				tempoPlayerPositionZ.z += PlayerSize;
				blockZ = floor(tempoPlayerPositionZ.z);
			}

			if (tempoPlayerPositionZ.y == round(tempoPlayerPositionZ.y))
			{

				blockX = floor(tempoPlayerPositionZ.x);
				blockY = tempoPlayerPositionZ.y;

				if (collisionMap[blockY - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 1].end())
				{
					directionVector.z = 0.0f;
				}
				if (collisionMap[blockY - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 2].end())
				{
					directionVector.z = 0.0f;
				}
			}
			else
			{
				blockX = floor(tempoPlayerPositionZ.x);
				blockY = ceil(tempoPlayerPositionZ.y);

				if (collisionMap[blockY - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 1].end())
				{
					directionVector.z = 0.0f;
				}
				if (collisionMap[blockY - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 2].end())
				{
					directionVector.z = 0.0f;
				}
				if (collisionMap[blockY - 3].find(std::make_pair(blockX, blockZ)) != collisionMap[blockY - 3].end())
				{
					directionVector.z = 0.0f;
				}
			}
		}
	}
	
	bool CollisionDetection::testForVerticalCollision(glm::vec3 playerPosition, float velocity, Camera_Movement direction) 
	{
		float blockX;
		float blockZ;
		//should check collision for the 4 blocks above, not just 1
		if (direction == UP)
		{
			playerPosition.y += velocity;
			playerPosition.y += PlayerSize;
			playerPosition.y = ceil(playerPosition.y);
			

			blockZ = floor(playerPosition.z);
			blockX = floor(playerPosition.x);

			if (collisionMap[(int)playerPosition.y - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[(int)playerPosition.y - 1].end())
			{
				return false;
			}
			else
				return true;
		}
		//should check collision for the 4 blocks under, not just 1
		if (direction == DOWN)
		{
			playerPosition.y -= velocity;

			playerPosition.y = floor(playerPosition.y);

			blockZ = floor(playerPosition.z);
			blockX = floor(playerPosition.x);

			if (collisionMap[(int)playerPosition.y - 2].find(std::make_pair(blockX, blockZ)) != collisionMap[(int)playerPosition.y - 2].end())
			{
				if (collisionMap[(int)playerPosition.y - 1].find(std::make_pair(blockX, blockZ)) != collisionMap[(int)playerPosition.y - 1].end())
				{
					return false;
				}
					
			}
			else
				return true;
		}
	}

	void CollisionDetection::placeBlock(glm::vec3 startingPosition, glm::vec3 ray)
	{
		glm::vec3 basePos = startingPosition;

		for (int i = 0; i < BlockPlacementRange; i++)
		{
			startingPosition += ray * 1.0f;
			auto rayTarget = startingPosition;
			rayTarget.x = floor(rayTarget.x);
			rayTarget.y = ceil(rayTarget.y);
			rayTarget.z = floor(rayTarget.z);
			rayTarget.y -= 1.0f;
			auto targetedBlock = collisionMap[rayTarget.y].find(std::make_pair(rayTarget.x, rayTarget.z));
			if (targetedBlock != collisionMap[rayTarget.y].end())
			{
				//float hint = glm::degrees(acos(glm::dot(glm::normalize(basePos), glm::normalize(startingPosition))));
				//std::cout << hint << "\n";
				glm::vec3 offset = startingPosition - basePos;
				float offsetByX = offset.x;
				float offsetByY = offset.y;
				float offsetByZ = offset.z;

				if (offsetByX < 0.0f)
					offsetByX *= -1.0f;
				if (offsetByZ < 0.0f)
					offsetByZ *= -1.0f;
				if (offsetByY < 0.0f)
					offsetByY *= -1.0f;

				if (offsetByX > offsetByZ)
				{
					if (offset.x > 0.0f) //looking towards positive x.
					{
						if (offset.y > PlayerSize) //looking at the bottom of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y - 1.0f, rayTarget.z);
							collisionMap[rayTarget.y - 1.0f].insert(std::make_pair(rayTarget.x, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;

						}
						else if (offset.y > -1.0f && offset.y < 1.0f) //looking at the middle of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x - 1.0f, rayTarget.y, rayTarget.z);
							collisionMap[rayTarget.y].insert(std::make_pair(rayTarget.x - 1.0f, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;
						}
						else if (offset.y < PlayerSize) //looking at the top of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y + 1.0f, rayTarget.z);
							collisionMap[rayTarget.y + 1.0f].insert(std::make_pair(rayTarget.x, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;
						}

					}
					if (offset.x < 0.0f) //looking towards negative x.
					{
						if (offset.y > PlayerSize) //looking at the bottom of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y - 1.0f, rayTarget.z);
							collisionMap[rayTarget.y - 1.0f].insert(std::make_pair(rayTarget.x, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;
						}
						else if (offset.y > -1.0f && offset.y < 1.0f) //looking at the middle of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x + 1.0f, rayTarget.y, rayTarget.z);
							collisionMap[rayTarget.y].insert(std::make_pair(rayTarget.x + 1.0f, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;
						}
						else if (offset.y < PlayerSize) //looking at the top of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y + 1.0f, rayTarget.z);
							collisionMap[rayTarget.y + 1.0f].insert(std::make_pair(rayTarget.x, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;
						}
					}
				}
				else
				{
					if (offset.z > 0.0f) //looking towards positive Z.
					{
						if (offset.y > PlayerSize) //looking at the bottom of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y - 1.0f, rayTarget.z);
							collisionMap[rayTarget.y - 1.0f].insert(std::make_pair(rayTarget.x, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;

						}
						else if (offset.y > -1.0f && offset.y < 1.0f) //looking at the middle of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y, rayTarget.z - 1.0f);
							collisionMap[rayTarget.y].insert(std::make_pair(rayTarget.x, rayTarget.z - 1.0f));
							ChunkController::placeBlock(newBlock);
							break;
						}
						else if (offset.y < PlayerSize) //looking at the top of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y + 1.0f, rayTarget.z);
							collisionMap[rayTarget.y + 1.0f].insert(std::make_pair(rayTarget.x, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;
						}

					}
					if (offset.z < 0.0f) //looking towards negative z.
					{
						if (offset.y > PlayerSize) //looking at the bottom of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y - 1.0f, rayTarget.z);
							collisionMap[rayTarget.y - 1.0f].insert(std::make_pair(rayTarget.x, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;
						}
						else if (offset.y > -1.0f && offset.y < 1.0f) //looking at the middle of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y, rayTarget.z + 1.0f);
							collisionMap[rayTarget.y].insert(std::make_pair(rayTarget.x, rayTarget.z + 1.0f));
							ChunkController::placeBlock(newBlock);
							break;
						}
						else if (offset.y < PlayerSize) //looking at the top of the block
						{
							glm::vec3 newBlock = glm::vec3(rayTarget.x, rayTarget.y + 1.0f, rayTarget.z);
							collisionMap[rayTarget.y + 1.0f].insert(std::make_pair(rayTarget.x, rayTarget.z));
							ChunkController::placeBlock(newBlock);
							break;
						}
					}
				}
			}
		}
	}
	void CollisionDetection::removeBlock(glm::vec3 startingPosition, glm::vec3 ray)
	{
		for (int i = 0; i < BlockPlacementRange; i++)
		{
			startingPosition += ray * 1.0f;
			auto rayTarget = startingPosition;
			rayTarget.x = floor(rayTarget.x);
			rayTarget.y = ceil(rayTarget.y);
			rayTarget.z = floor(rayTarget.z);
			rayTarget.y -= 1.0f;

			auto block = collisionMap[rayTarget.y].find(std::make_pair(rayTarget.x, rayTarget.z));
			if (block != collisionMap[rayTarget.y].end())
			{
				ChunkController::removeBlock(rayTarget);
				collisionMap[rayTarget.y].erase(block);
				break;
			}
		}
	}
}