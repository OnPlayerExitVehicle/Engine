#version 330 core


uniform vec4 VEC_Color;
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
        fragColor = VEC_Color;
    }
    
}