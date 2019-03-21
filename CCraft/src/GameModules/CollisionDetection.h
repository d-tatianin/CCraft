#pragma once
#include <set>
#include <array>
#include "../vendor/glm/glm.hpp"
#include <iostream>
#include <math.h>

#define WORLD_HEIGHT 128

namespace CCraft
{
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class CollisionDetection
	{
	private:
		static std::array<std::set<std::pair<float, float>>, WORLD_HEIGHT> collisionMap; //each element in the array represents a collision map for a particular Y.
	public:
		static void addCollisionElement(glm::vec3 coords);
		static void removeCollisionElement(glm::vec3 coords);
		void testForCollision(glm::vec3 playerPosition, glm::vec3& directionVector, Camera_Movement direction, float velocity);
		bool testForVerticalCollision(glm::vec3 playerPosition, float velocity, Camera_Movement direction);
		void placeBlock(glm::vec3 startingPosition, glm::vec3 ray);
		void removeBlock(glm::vec3 startingPosition, glm::vec3 ray);
	};
}