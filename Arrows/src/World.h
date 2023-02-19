#pragma once

#include "Grid.h"

#include <kwee/kwee.h>
#include <array>

class World : public kwee::Scene
{
private:

	

public:

	Grid* grid;
	kwee::GameObject* phantomArrow;

	World();
	~World();

};

