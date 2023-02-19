#pragma once

#include "elements/Arrow.h"
#include "elements/Wire.h"
#include "elements/DoubleWire.h"
#include "elements/Block.h"

#include <kwee/kwee.h>

enum class ArrowType
{
	Wire, DoubleWire, Block, Not, And, Or
};

class Grid : public kwee::GameObject
{
private:

	glm::vec2 size_;
	Direction dir_;
	bool hover = false;

public:

	ArrowType at = ArrowType::Wire;

	Arrow*** arrows;
	int** signals;

	void sendSignal(glm::ivec2 source, glm::ivec2 offset);
	void simulate();

	Grid(glm::vec2 size);
	~Grid();

	void update() override;

	void onMouseHover() override;
	void onMouseHoverEnter() override;
	void onMouseHoverExit() override;

	glm::ivec2 WorldToGrid(glm::vec2 worldCoords);
	Arrow* createArrow(Grid* grid, Direction dir);
};

