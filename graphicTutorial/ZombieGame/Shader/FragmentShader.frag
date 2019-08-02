#version 330 core

out vec4 fragColor;

in vec4 color;
in vec2 fragPos;
in vec2 texCord;

uniform sampler2D image;

void main()
{
	fragColor = texture(image,vec2(texCord.x, 1.0f - texCord.y)) * color;
	 
}
