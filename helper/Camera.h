#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/matrix.hpp>

struct Camera 
{
	glm::vec3 CameraFront = { 0.0f, 0.0f, -1.0f };
	glm::vec3 CameraPos = { 0.0f, 0.0f, 3.0f };
	glm::vec3 CameraUp = { 0.0f, 1.0f, 0.0f };



	glm::mat4 GetView()
	{
		return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
	}
};
