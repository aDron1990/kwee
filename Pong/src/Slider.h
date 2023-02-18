#pragma once

#include <kwee/kwee.h>

class Slider : public kwee::GameObject
{
private:

public:

	Slider() : GameObject({ 0, 1, 0 })
	{
		createCollider(1, 0);
		setScale({ 0.5, 3 });
	}

	~Slider()
	{

	}
};

