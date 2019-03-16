#pragma once
#include <unordered_map>
#include <vector>
#include "../vendor/glm/glm.hpp"

namespace CCraft
{
	class Collision
	{
	private:
		static std::vector<std::unordered_map<float, float>> collisionMap;
	public:
		Collision();
		void setCollisionMap(glm::vec3* blocks);
		void addCollisionElement(glm::vec3 coords);
		void removeCollisionElement(glm::vec3 coords);
	};
}