#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexture;
layout(location = 2) in vec3 inNormal;

uniform mat4 MTX_Transform;
uniform mat4 MTX_View;
uniform mat4 MTX_Projection;

out vec2 outTexture;
out vec3 outNormal;
out vec3 outFragPos;

void main()
{
    mat4 combinedMatrix = MTX_Projection * MTX_View * MTX_Transform;
    gl_Position = combinedMatrix * vec4(inPosition, 1.0f);

    outTexture = inTexture;

    outFragPos = vec3(MTX_Transform * vec4(inPosition, 1.0f));
    outNormal = inNormal;
}
