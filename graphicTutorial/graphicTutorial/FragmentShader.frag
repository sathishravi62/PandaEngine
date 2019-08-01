#version 330 core

out vec4 fragColor;

in vec4 color;
in vec2 fragPos;
in vec2 texCord;

uniform float time;
uniform sampler2D image;

void main()
{
	fragColor = texture(image,vec2(texCord.x, 1.0f - texCord.y)) * vec4(color.r * (cos(fragPos.x * 4.0 + time)+1.0) * 0.5,
					 color.g * (cos(fragPos.y * 8.0 + time)+1.0) * 0.5,
					 color.b * (cos(fragPos.x * 2.0 + time)+1.0) * 0.5,1.0f);
	 
}
