#version 330 core

struct Material
{
    vec3 color;
};
uniform Material material;

uniform bool B_IsTextured;
uniform sampler2D myTexture;

in vec2 outTexture;

out vec4 fragColor;

void main()
{
    if(B_IsTextured)
    {
        fragColor = texture(myTexture, outTexture);
    }
    else
    {
        fragColor = vec4(material.color, 1.0f);
    }
}