#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;

out vec4 color;
out vec2 fragPos;
out vec2 texCord;

uniform mat4 p;

void main()
{
	gl_Position = (p *  vec4(vertex,0.0f,1.0f));
	
	

	color = aColor;
	fragPos = vertex;
	texCord = aTex;
}
