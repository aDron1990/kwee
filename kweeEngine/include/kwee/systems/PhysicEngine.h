#pragma once

#include "kwee/game_primitives/Collider.h"

#include <vector>

namespace kwee
{
	class Rect
	{
	public:

		glm::vec2 v11 = glm::vec2(0.0f);
		glm::vec2 v12 = glm::vec2(0.0f);
		glm::vec2 v21 = glm::vec2(0.0f);
		glm::vec2 v22 = glm::vec2(0.0f);

	};

	class PhysicEngine
	{
	private:

		static std::vector<Collider*> colliders_;
		static std::vector<int> requiedToRemoveCollidersIds_;

		static void removeRequiedObjects();

	public:

		static void addCollider(Collider* c);
		static void removeCollider(Collider* c);

		static void update();
		static bool checkCollisions(Collider* c1, Collider* c2);
		static bool isPointInRect(glm::vec2 point, Rect rect);

	};
}