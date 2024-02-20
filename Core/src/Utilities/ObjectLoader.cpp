#include "ObjectLoader.h"
#include "MeshFactory.h"
#include "Mesh.h"
#include <iostream>
#include <format>
#include <string>
#include <sstream>
#include <GLM/glm/geometric.hpp>

ObjectLoader::ObjectLoader()
{
	
}

ObjectLoader::~ObjectLoader()
{

}

std::shared_ptr<Mesh> ObjectLoader::LoadObject(_STRING_CR_ path)
{
	std::ifstream file(path);

	if(!file.is_open())
	{
		DEBUG_FORMAT("[Error] Can't open file: {}", path);
		return nullptr;
	}

	std::string line;
	float f1, f2, f3;
	unsigned int u1, u2, u3;
	float zeroF = 0.f;

	std::vector<unsigned int> indexList;
	std::vector<MeshFactory::TexturedVertex> vertexList;

	while(!std::getline(file, line).eof())
	{
		//DEBUG_LOG(line);
		std::istringstream iss(line);
		std::string header;
		iss >> header;

		if(line[0] == 'v')
		{
			iss >> f1 >> f2 >> f3;
			DEBUG_FORMAT("[Information] f1 = {}, f2 = {} = f3 = {}", f1, f2, f3);

			MeshFactory::TexturedVertex vert = {
				glm::vec3(f1, f2, f3),
				glm::vec2(zeroF, zeroF),
				glm::vec3(1.f, 1.f, 1.f)
			};
			vertexList.push_back(std::move(vert));

			//vertices.push_back(std::move(glm::vec3(f1, f2, f3)));
		}
		else if (line[0] == 'f')
		{
			iss >> u1 >> u2 >> u3;
			indexList.push_back(u1 - 1);
			indexList.push_back(u2 - 1);
			indexList.push_back(u3 - 1);
		}
	}

	/*int size = indexList.size();

	bool b = false;
	for(int i = 0; i < (size / 3); i++)
	{
		int it = i * 3;

		glm::vec3 normal;

		if(!b)
			normal = glm::cross(vertices[indexList[it + 1]], vertices[indexList[it]]);
		else
			normal = glm::cross(vertices[indexList[it]], vertices[indexList[it + 1]]);

		b = !b;
		for(int j = 0; j < 3; j++)
		{
			MeshFactory::TexturedVertex vert = {
				std::move(vertices[indexList[it + j]]),
				glm::vec2(zeroF, zeroF),
				std::move(normal)
			};

			vertexList.push_back(std::move(vert));
			indexList[it + j] = vertexList.size() - 1;
		};
	}*/

	return std::make_shared<Mesh>(vertexList, indexList);

	//DEBUG_FORMAT("[Information] Vertex line count = {}, Index line count = {}", v, f);
}