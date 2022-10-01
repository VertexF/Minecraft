#version 330

out vec4 outColour;
in vec2 passTextureCoord;

uniform sample2D texSampler;

void main()
{
    outColour = texture(texSampler, passTextureCoord);
}