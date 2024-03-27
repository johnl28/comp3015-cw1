#pragma once
#include <glm/glm.hpp>
#include "Model.h"

struct PointLight {

	int Id = 0;

	glm::vec3 Color = { 1.0f, 1.0f, 1.0f };
	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };

	Model* model = nullptr;
};

