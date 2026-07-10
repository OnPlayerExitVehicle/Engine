#include "TextureLoader.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

std::shared_ptr<Texture> TextureLoader::LoadTexture(const void* data, int width, int height, int internalFormat, unsigned int format) noexcept
{
    if(height == 0)
    {
        int channels = 4;
        data = stbi_load_from_memory((uint8_t*)data, width, &width, &height, nullptr, STBI_rgb_alpha);
        assert(data);
        format = GL_RGBA;
    }

    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return std::make_shared<Texture>(id);
}

std::shared_ptr<Texture> TextureLoader::LoadTexture(const std::string& path)
{
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data == nullptr)
    {
        std::cout << "File cannot be loaded! Path = " << path << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }

    std::shared_ptr<Texture> tex = LoadTexture(data, width, height, GL_RGBA, GL_RGBA);
    stbi_image_free(data);
    return tex;
}