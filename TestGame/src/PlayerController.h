#pragma once

class Cube;
class PlayerController
{
	static float cubeSpeed;

public:

	static Cube* controlled[2];

	static void update();
	static void switchPlayers();
};

