#pragma once

#include <kwee/kwee.h>

class Ball : public kwee::GameObject
{
private:

	glm::vec2 dir {1, 1};
	float speed;

public:

	Ball() : GameObject({ 1, 0, 0 }), speed(0.002)
	{
		createCollider(1, 0);
		setScale({0.5, 0.5});
	}

	void changeVertDir()
	{
		dir.y = -dir.y;
	}

	void changeHorDir()
	{
		dir.x = -dir.x;
	}

	void onCollisionEnter(kwee::Collider* other) override
	{
		changeHorDir();
	}

	void onCollisionExit(kwee::Collider* other) override
	{
		speed += 0.0005;
	}

	void move()
	{
		setPosition(getPosition() + dir * ((float)speed * kwee::PhysicEngine::getDelta()));
	}
};