#version 450 core

layout(location = 0) in vec3 inVertexPosition;

out vec2 passTextureCoord;

uniform mat4 projViewMatrix;
uniform mat viewMatrix;

void main()
{
    gl_Position = projViewMatrix * viewMatrix * vec4(inVertexPosition, 1.0);
    passTextureCoord = inTextureCoord;
}