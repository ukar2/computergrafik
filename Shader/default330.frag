#version 450

layout(location = 0)in vec4 texC;
layout(location = 0)out vec4 fragColor;

uniform sampler2D texture;

void main()
{
    gl_FragColor = texture2D(texture, vec2(texC.x, texC.y));
}
