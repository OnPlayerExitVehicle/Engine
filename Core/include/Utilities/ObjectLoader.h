#pragma once
#include <fstream>
#include "Globals.h"
#include <unordered_map>
#include <functional>
#include <memory>

class Mesh;
class Scene;
class GameObject;

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();
	std::shared_ptr<GameObject> LoadGameObject(Scene* scene, _STRING_CR_ path);

private:
	//std::unordered_map<int, std::function<std::vector<unsigned int>&(int*, int)>> lineFunctionMap;
};