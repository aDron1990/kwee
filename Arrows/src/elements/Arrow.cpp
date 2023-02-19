#include "Arrow.h"
#include "../Grid.h"

#include <iostream>

Arrow::Arrow(Grid* grid, Direction dir, std::string activeTextrureName, std::string unactiveTextrureName) : GameObject(unactiveTextrureName), dir_(dir), grid_(grid), state_(false)
{
	activeTexture_ = kwee::ResourceManager::getTexture(activeTextrureName);
	unactiveTexture_ = kwee::ResourceManager::getTexture(unactiveTextrureName);

	setRotation(dir_.getDegrees());
}

void Arrow::setState(bool state)
{
	state_ = state;
	if (state_)
		setTexture(activeTexture_);
	else
		setTexture(unactiveTexture_);
}

bool Arrow::getState()
{
	return state_;
}

void Arrow::sendSignal(glm::ivec2 offset)
{
	grid_->sendSignal(grid_->WorldToGrid(getPosition()), offset);
}

void Arrow::rotate_plus()
{
	dir_.rotate_plus();
	setRotation(dir_.getDegrees());
}

void Arrow::rotate_minus()
{
	dir_.rotate_minus();
	setRotation(dir_.getDegrees());
}

Direction Arrow::getDir()
{
	return dir_;
}

void Arrow::action()
{
	
}