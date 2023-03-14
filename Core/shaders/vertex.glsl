#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexture;

uniform mat4 MTX_Transform;
uniform mat4 MTX_View;
uniform mat4 MTX_Projection;

out vec2 outTexture;

void main()
{
    mat4 combinedMatrix = MTX_Projection * MTX_View * MTX_Transform;
    gl_Position = combinedMatrix * vec4(inPosition, 1.0f);
    outTexture = inTexture;
}