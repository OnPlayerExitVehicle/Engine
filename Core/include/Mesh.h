#pragma once
#include <vector>
#include <memory>
#include <GLM/glm/vec3.hpp>
#include "MeshFactory.h"

class Mesh
{
private:
	unsigned int vao;
	int indexCount;

public:
	Mesh(const std::vector<MeshFactory::TexturedVertex>& vertexVector, const std::vector<unsigned int>& indexVector);
	void Draw() const;
};