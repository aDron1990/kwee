#include "kwee/systems/Input.h"

#include <memory>

bool kwee::Input::key[512] = { 0 };
bool kwee::Input::key_up[512] = { 0 };
bool kwee::Input::key_down[512] = { 0 };

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_REPEAT)	kwee::Input::setKey(key, action);
}

void kwee::Input::initialize(GLFWwindow* window)
{
	memset(key, 0, sizeof(key));
	memset(key_up, 0, sizeof(key_up));
	memset(key_down, 0, sizeof(key_down));

	glfwSetKeyCallback(window, key_callback);
}

void kwee::Input::terminate(GLFWwindow* window)
{
	glfwSetKeyCallback(window, 0);
}

void kwee::Input::update()
{
	memset(key_up, 0, sizeof(key_up));
	memset(key_down, 0, sizeof(key_down));
}

void kwee::Input::setKey(int code, bool action)
{
	if (action)
	{
		key[code] = true;
		key_down[code] = true;
	}
	else
	{
		key[code] = false;
		key_up[code] = true;
	}
}

bool kwee::Input::getKey(int code)
{
	return key[code];
}

bool kwee::Input::getKeyUp(int code)
{
	return key_up[code];
}

bool kwee::Input::getKeyDown(int code)
{
	return key_down[code];
}