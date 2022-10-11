#version 450 core

layout(location = 0) in vec3 inVertexPosition;
layout(location = 1) in vec2 inTextureCoord;
layout(location = 2) in float inCardinalLight;

out vec2 passTextureCoord;
out float passCardinalLight;

uniform mat4 projViewMatrix;
uniform float time;

vec4 getWorldPosition()
{
    vec3 vertexPosition = inVertexPosition;
    vertexPosition.y += sin((time + vertexPosition.x) * 1.5) / 8.8f;
    vertexPosition.y += cos((time + vertexPosition.z) * 1.5) / 8.1f
    vertexPosition.y -= 0.2;

    return vec4(vertexPosition, 1);
}

void main()
{
    gl_Position = projViewMatrix * getWorldPosition();
    passTextureCoord = inTextureCoord;
    passCardinalLight = inCardinalLight;
}