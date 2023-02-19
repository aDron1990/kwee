#pragma once

#include <kwee/kwee.h>

class Direction
{
private:

	int degrees = 0;

public:

	Direction() {}

	Direction(int dr)
	{
		degrees = dr * 90;
	};

	void rotate_plus()
	{
		degrees += 90;
		if (degrees == 360) degrees = 0;
	}

	void rotate_minus()
	{
		degrees -= 90;
		if (degrees == -90) 
			degrees = 270;
	}

	int getDegrees()
	{
		return degrees;
	}

	glm::ivec2 getGridOffset()
	{
		switch (degrees)
		{
		case 0: return glm::ivec2{0, 1};
		case 90: return glm::ivec2{ -1, 0 };
		case 180: return glm::ivec2{ 0, -1 };
		case 270: return glm::ivec2{ 1, 0 };
		}
	}
};

class Grid;
class Arrow : public kwee::GameObject
{
private:

	Grid* grid_;
	bool state_;

	Direction dir_;

	std::shared_ptr<kwee::Texture> activeTexture_;
	std::shared_ptr<kwee::Texture> unactiveTexture_;

protected:

	void sendSignal(glm::ivec2 offset);

public:

	Arrow(Grid* grid, Direction dir, std::string activeTextrureName, std::string unactiveTextrureName);

	void setState(bool state);
	bool getState();

	virtual void setSignals(int sig) = 0;

	void rotate_plus();
	void rotate_minus();

	Direction getDir();

	virtual void action();
};

