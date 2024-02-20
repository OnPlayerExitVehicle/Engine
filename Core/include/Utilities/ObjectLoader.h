#pragma once
#include <fstream>
#include "Globals.h"
#include <unordered_map>
#include <functional>

class Mesh;

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();
	std::shared_ptr<Mesh> LoadObject(_STRING_CR_ path);

private:
	//std::unordered_map<int, std::function<std::vector<unsigned int>&(int*, int)>> lineFunctionMap;
};