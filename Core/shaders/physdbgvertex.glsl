#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

uniform mat4 MTX_View;
uniform mat4 MTX_Projection;

out vec3 outColor;

void main()
{
    gl_Position = MTX_Projection * MTX_View * vec4(inPosition, 1.0f);
    outColor = inColor;
}
