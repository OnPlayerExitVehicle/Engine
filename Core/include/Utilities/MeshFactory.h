#pragma once
#include <map>
#include <iostream>
#include "Globals.h"
#include "GLM/glm/vec3.hpp"
#include "GLM/glm/vec2.hpp"
#include <vector>
#include <memory>

class Mesh;

enum class MeshType
{
	Cube
};

class MeshFactory
{
private:
	static std::map<MeshType, std::shared_ptr<Mesh>> meshMap;
	

public:
	static std::shared_ptr<Mesh> GetMesh(MeshType type);

	class TexturedVertex
	{
	public:
		glm::vec3 pos;
		glm::vec2 tex;
	};
};