#pragma once

#include <kwee/game_primitives/GameObject.h>

class Cube : public kwee::GameObject
{
public:

	bool controlled;
	Cube(bool started);

//	void update() override;
	void onCollisionEnter(kwee::Collider* other) override;

};
