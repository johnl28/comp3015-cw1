#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/matrix.hpp>

struct Camera 
{
	glm::vec3 CameraFront = { 0.0f, 0.0f, -1.0f };
	glm::vec3 CameraPos = { 0.0f, 0.0f, 3.0f };
	glm::vec3 CameraUp = { 0.0f, 1.0f, 0.0f };

	float Speed = 0.5f;
	float Pitch = 0.0f;
	float Yaw = -90.0f;


	glm::mat4 GetView()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		direction.y = sin(glm::radians(Pitch));
		direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		CameraFront = glm::normalize(direction);

		return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
	}
};
