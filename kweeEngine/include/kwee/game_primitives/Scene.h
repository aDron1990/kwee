#pragma once

#include "kwee/core/api.h"
#include "GameObject.h"
#include "kwee/game_primitives/Camera.h"
#include "kwee/graphics/Color.h"

#include <vector>

namespace kwee
{
	class KWEEAPI Scene
	{
	private:

		std::vector<GameObject*> objects_;

	protected:

		Camera* mainCamera_;

	public:

		Color background = {1, 1, 1};

		Scene();
		virtual ~Scene();

		void draw();
		void update();

		void addObject(GameObject* object);
		void removeObject(GameObject* object);

		Camera* getCamera();
	};
}