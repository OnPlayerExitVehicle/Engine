#include "TextureLoader.h"

#include <GLAD/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

std::shared_ptr<Texture> TextureLoader::LoadTexture(const std::string& path)
{
    std::cout << "Path = " << path << std::endl;
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    int width, height, nrChannels;

    stbi_uc* texture = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb);
    if (texture == nullptr)
    {
        std::cout << "File cannot be loaded! Path = " << path << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(texture);
    return std::make_shared<Texture>(id);
}