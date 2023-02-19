#include "Cube.h"
#include "PlayerController.h"

#include <iostream>
#include <kwee/systems/Input.h>
#include <kwee/game_primitives/Scene.h>

Cube::Cube(bool started) : GameObject("test"), controlled(started)
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

void Cube::update()
{
	if (drag)
	{
		setPosition(getOwnerScene()->getCamera()->ScreenToWorld(kwee::Input::getMousePosition()));
	}
}

void Cube::onMouseHover()
{
//	std::cout << kwee::Input::getMouseButtonDown(0);
	if (kwee::Input::getMouseButtonDown(0))
	{
		//std::cout << "drag" << std::endl;
		drag = true;
	}
	if (kwee::Input::getMouseButtonUp(0))
	{
		drag = false;
	}
}

void Cube::onMouseHoverEnter()
{
	colliderIsDrawing = true;
}

void Cube::onMouseHoverExit()
{
	colliderIsDrawing = false;
	drag = false;
}