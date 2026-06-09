#version 300 es
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;

out vec4 color;
out vec2 texCoord;

uniform float uAspect;
void main() { 
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	color = aColor;	
	texCoord = aTex;
}