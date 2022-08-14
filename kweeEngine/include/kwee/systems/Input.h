#pragma once

#include "kwee/core/api.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace kwee
{
	class KWEEAPI Input
	{
	private:

		static bool key[512];
		static bool key_down[512];
		static bool key_up[512];

	public:

		static void initialize(GLFWwindow* window);
		static void terminate(GLFWwindow* window);

		static void update();
		static void setKey(int code, bool action);
		static bool getKey(int code);
		static bool getKeyUp(int code);
		static bool getKeyDown(int code);

	};
}