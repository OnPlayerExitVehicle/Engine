#pragma once
#include <memory>
#include <iostream>
#include "Texture.h"

class TextureLoader
{
public:
	static std::shared_ptr<Texture> LoadTexture(const void* data, int width, int height, int internalFormat, unsigned int format) noexcept;
	static std::shared_ptr<Texture> LoadTexture(const std::string& path);
};