#pragma once
#include <GLM/glm/vec3.hpp>

struct Material
{
public:
	glm::vec3 color = glm::vec3(1.0f);
	float ambient = 1.0f;
	float diffuse = 1.0f;
	float specular = 0.5f;
	int shininess = 32;
};

struct LightMaterial
{
public:
	float ambient = 0.2f;
	float diffuse = 0.5f;
	float specular = 1.0f;
};