#pragma once

class Texture
{
private:
	unsigned int id;
public:
	Texture(unsigned int id);
	void Bind();
};