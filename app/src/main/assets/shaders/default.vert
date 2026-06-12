#version 300 es
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;

out vec4 color;
out vec2 texCoord;

uniform vec2 uOffset;
uniform float uZoom;

void main() { 
	vec2 pos = vec2(aPos.x, aPos.y);
	pos = pos * uZoom;
	gl_Position = vec4(pos.x + uOffset.x, pos.y + uOffset.y, aPos.z, 1.0);
	color = aColor;	
	texCoord = aTex;
}