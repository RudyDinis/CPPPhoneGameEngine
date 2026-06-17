#version 300 es
precision mediump float;
in vec2 vUV;
uniform sampler2D tex0;
out vec4 fragColor;

void main()
{
    fragColor = texture(tex0, vUV);
}