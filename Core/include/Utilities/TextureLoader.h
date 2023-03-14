#pragma once
#include <memory>
#include <iostream>
#include "Texture.h"

class TextureLoader
{
public:
	static std::shared_ptr<Texture> LoadTexture(const std::string& path);
};