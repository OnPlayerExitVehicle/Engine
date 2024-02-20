#include "Texture.h"
#include <glad/glad.h>

Texture::Texture(unsigned int id) : id(id) { }

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}