#include "Camera.h"
#include <glm\gtx\transform.hpp>

const float MOUVEMENT_SPEED = 0.1f;
const float ROTATIONAL_SPEED = 0.5f;

Camera::Camera() : 
	viewDirection(0.0f, 0.0f, -1.0f),
	UP(0.0f, 1.0f, 0.0f)
{
}

void Camera::mouseUpdate(const glm::vec2 &newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 50.0f)
	{
		oldMousePosition = newMousePosition;
		return;
	}

	glm::vec3 toRotateAround = glm::cross(viewDirection, UP);

	glm::mat4 rotator =
		glm::rotate(-(mouseDelta.x * 3.1416f / 180.0f) * ROTATIONAL_SPEED, UP) *
		glm::rotate(-(mouseDelta.y * 3.1416f / 180.0f) * ROTATIONAL_SPEED, toRotateAround);

	viewDirection = glm::mat3(rotator) * viewDirection;

	oldMousePosition = newMousePosition;
}

void Camera::moveForward()
{
	position += MOUVEMENT_SPEED * viewDirection;
}

void Camera::moveBackward()
{
	position += -MOUVEMENT_SPEED * viewDirection;
}

void Camera::strafeLeft()
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	position += -MOUVEMENT_SPEED * strafeDirection;
}

void Camera::strafeRight()
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	position += MOUVEMENT_SPEED * strafeDirection;
}

void Camera::moveUp()
{
	position += MOUVEMENT_SPEED * UP;
}

void Camera::moveDown()
{
	position += -MOUVEMENT_SPEED * UP;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}