#include "MeshFactory.h"
#include "Mesh.h"

std::map<MeshType, std::shared_ptr<Mesh>> MeshFactory::meshMap;

std::shared_ptr<Mesh> MeshFactory::GetMesh(MeshType type)
{
	if (meshMap.count(type) > 0)
	{
		return meshMap[type];
	}
	if (type == MeshType::Cube)
	{
		/*std::vector<glm::vec3> vertexVector = {
			glm::vec3(-0.5f,  0.5f,  0.5f),
			glm::vec3(0.5f,  0.5f,  0.5f),
			glm::vec3(-0.5f, -0.5f,  0.5f),
			glm::vec3(0.5f, -0.5f,  0.5f),
			glm::vec3(-0.5f,  0.5f, -0.5f),
			glm::vec3(0.5f,  0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f)
		};*/

		glm::vec3 corners[8]{
			glm::vec3(-0.5f,  0.5f,  0.5f),
			glm::vec3(0.5f,  0.5f,  0.5f),
			glm::vec3(0.5f, -0.5f,  0.5f),
			glm::vec3(-0.5f, -0.5f,  0.5f),
			glm::vec3(-0.5f,  0.5f, -0.5f),
			glm::vec3(0.5f,  0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f)
		};

		std::vector<TexturedVertex> texturedVertexVector = {
			// Üst

			{corners[0], glm::vec2(0.0f, 1.0f)},
			{corners[1], glm::vec2(1.0f, 1.0f)},
			{corners[2], glm::vec2(1.0f, 0.0f)},
			{corners[3], glm::vec2(0.0f, 0.0f)},
			// Ön

			{corners[1], glm::vec2(0.0f, 1.0f)},
			{corners[5], glm::vec2(1.0f, 1.0f)},
			{corners[6], glm::vec2(1.0f, 0.0f)},
			{corners[2], glm::vec2(0.0f, 0.0f)},
			// Sað

			{corners[4], glm::vec2(0.0f, 1.0f)},
			{corners[5], glm::vec2(1.0f, 1.0f)},
			{corners[1], glm::vec2(1.0f, 0.0f)},
			{corners[0], glm::vec2(0.0f, 0.0f)},
			// Arka
			{corners[4], glm::vec2(0.0f, 1.0f)},
			{corners[0], glm::vec2(1.0f, 1.0f)},
			{corners[3], glm::vec2(1.0f, 0.0f)},
			{corners[7], glm::vec2(0.0f, 0.0f)},
			// Sol
			{corners[7], glm::vec2(0.0f, 1.0f)},
			{corners[6], glm::vec2(1.0f, 1.0f)},
			{corners[2], glm::vec2(1.0f, 0.0f)},
			{corners[3], glm::vec2(0.0f, 0.0f)},

			{corners[4], glm::vec2(0.0f, 1.0f)},
			{corners[5], glm::vec2(1.0f, 1.0f)},
			{corners[6], glm::vec2(1.0f, 0.0f)},
			{corners[7], glm::vec2(0.0f, 0.0f)}
		};

		std::vector<unsigned int> indexVector(36);
		for (int i = 0; i < 6; i++)
		{
			indexVector.push_back(i * 4);
			indexVector.push_back(i * 4 + 1);
			indexVector.push_back(i * 4 + 2);

			indexVector.push_back(i * 4);
			indexVector.push_back(i * 4 + 2);
			indexVector.push_back(i * 4 + 3);
		}

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(texturedVertexVector, indexVector);
		meshMap[type] = mesh;
		return mesh;
	}
	else
	{
		DEBUG_LOG("Wrong type specified!");
		return nullptr;
	}
}