#include "Cube.h"
#include "PlayerController.h"

#include <iostream>
#include <kwee/systems/Input.h>
#include <kwee/systems/Application.h>
#include <kwee/game_primitives/Scene.h>

Cube::Cube(bool started) : GameObject("test"), controlled(started)
{
	color = { 0, 1, 0 };
}

void Cube::onCollisionEnter(kwee::Collider* other)
{
	if (controlled)
	{
		colliderIsDrawing = false;
		controlled = false;
	}
	else
	{
		colliderIsDrawing = true;
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
	if (kwee::Input::getMouseButtonDown(0))
	{
		mix = 0.2;
		drag = true;
	}
	if (kwee::Input::getMouseButtonUp(0))
	{
		mix = 0;
		drag = false;
	}
}

void Cube::onMouseHoverEnter()
{
	
}

void Cube::onMouseHoverExit()
{
	drag = false;
}