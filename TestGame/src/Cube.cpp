#include "Cube.h"
#include "PlayerController.h"

#include <iostream>

Cube::Cube(bool started) : GameObject(kwee::Color{1, 0, 0}), controlled(started)
{
	
}

void Cube::onCollisionEnter(kwee::Collider* other)
{
	if (controlled)
	{
		controlled = false;
	}
	else
	{
		controlled = true;
	}
}
 