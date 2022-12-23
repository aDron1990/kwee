#include "Cube.h"
#include "PlayerController.h"

#include <iostream>

Cube::Cube(bool started) : GameObject("rectangle", "testShader"), controlled(started)
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
 