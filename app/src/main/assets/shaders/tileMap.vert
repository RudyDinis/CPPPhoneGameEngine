
#version 300 es
layout(location = 0) in vec2 aPos;     // quad local 0..1
layout(location = 1) in vec2 aUV;      // uv local 0..1
layout(location = 2) in vec4 aInstancePosSize; // x, y, w, h
layout(location = 3) in vec4 aInstanceUVRect;  // u0, v0, u1, v1

uniform vec2 uScreenSize;
uniform vec2 uOffset;
uniform float uZoom;

out vec2 vUV;

void main()
{
    vec2 local = vec2(1.0) - aPos;
    vec2 pos = aInstancePosSize.xy + local * aInstancePosSize.zw;

    // apply zoom (centered if needed later)
    pos *= uZoom;

    // apply offset in pixels
    pos += uOffset;

    vec2 ndc = (pos / uScreenSize) * 2.0 - 1.0;
    ndc.y = -ndc.y;

    gl_Position = vec4(ndc, 0.0, 1.0);

    vUV = mix(aInstanceUVRect.xy, aInstanceUVRect.zw, aUV);
}