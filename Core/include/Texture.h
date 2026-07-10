#pragma once

class Texture
{
private:
    unsigned int id = -1;
public:
	Texture(unsigned int id);
	void Bind();
    inline constexpr unsigned int GetId() const noexcept { return id; }
};
