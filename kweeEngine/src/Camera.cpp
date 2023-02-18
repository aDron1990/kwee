#include "kwee/game_primitives/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

kwee::Camera::Camera(glm::vec4 viewport) : viewport_(viewport)
{
	aspect_ = viewport_[2] / viewport_[3];
	projection_ = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / aspect_, 1.0f, 1.0f));
}

glm::mat4 kwee::Camera::getProjectionMatrix()
{
	return projection_;
}

glm::mat4 kwee::Camera::getViewMatrix()
{
	return getTransformMatrix();
}

void kwee::Camera::useViewport()
{
	glViewport(viewport_[0], viewport_[1], viewport_[2], viewport_[3]);
}

glm::vec2 kwee::Camera::ScreenToWorld(glm::vec2 screenCoords)
{
	screenCoords -= glm::vec2{ viewport_[2] / 2, viewport_[3] / 2};
	screenCoords.y = -screenCoords.y;
	screenCoords /= (viewport_[2] < viewport_[3] ? viewport_[2] : viewport_[3]) / 2;
	screenCoords *= glm::vec2{ 1.0f } / getScale();
	return screenCoords;
}