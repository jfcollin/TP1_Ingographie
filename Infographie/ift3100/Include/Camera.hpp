#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <Macros.hpp>


const float MOUVEMENT_SPEED = 0.1f;
const float ROTATIONAL_SPEED = 0.5f;


class Camera
{

	glm::vec3 position;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	glm::vec2 oldMousePosition;


public:

	Camera() : 
		viewDirection(0.0f, 0.0f, -1.0f),
		UP(0.0f, 1.0f, 0.0f)
	{
	}

	void mouseUpdate(const glm::vec2 &newMousePosition)
	{
		glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
		if (glm::length(mouseDelta) > 50.0f)
		{
			oldMousePosition = newMousePosition;
			return;
		}

		glm::vec3 toRotateAround = glm::cross(viewDirection, UP);

		glm::mat4 rotator =
			glm::rotate(-(mouseDelta.x * PI / 180.0f) * ROTATIONAL_SPEED, UP) *
			glm::rotate(-(mouseDelta.y * PI / 180.0f) * ROTATIONAL_SPEED, toRotateAround);

		viewDirection = glm::mat3(rotator) * viewDirection;

		oldMousePosition = newMousePosition;
	}

	glm::mat4 getViewMatrix() const
	{
		return glm::lookAt(position, position + viewDirection, UP);
	}

	void moveForward()
	{ 
		position += MOUVEMENT_SPEED * viewDirection; 
	}

	void moveBackward()
	{ 
		position += -MOUVEMENT_SPEED * viewDirection; 
	}

	void strafeLeft()
	{
		glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
		position += -MOUVEMENT_SPEED * strafeDirection;
	}

	void strafeRight()
	{
		glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
		position += MOUVEMENT_SPEED * strafeDirection;
	}

	void moveUp()
	{
		position += MOUVEMENT_SPEED * UP;
	}

	void moveDown()
	{
		position += -MOUVEMENT_SPEED * UP;
	}

};

#endif // !CAMERA_HPP


