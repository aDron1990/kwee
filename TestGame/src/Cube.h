#pragma once

#include <kwee/game_primitives/GameObject.h>

class Cube : public kwee::GameObject
{
public:

	bool controlled;
	bool drag = false;
	Cube(bool started);

	void update() override;
	void onCollisionEnter(kwee::Collider* other) override;

	void onMouseHover() override;
	void onMouseHoverEnter() override;
	void onMouseHoverExit() override;
};
