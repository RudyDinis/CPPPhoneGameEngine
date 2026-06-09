#version 300 es
precision mediump float;
out vec4 fragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{ 
	fragColor = texture(tex0, texCoord);
}
