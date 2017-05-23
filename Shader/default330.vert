#version 450

layout(location = 0)uniform mat4 projektionMatrix;
layout(location = 1)uniform mat4 viewMatrix;
layout(location = 2)uniform mat4 modelMatrix;

layout(location = 0)in vec4 vert;
layout(location = 3)in vec4 texCoord;
layout(location = 0)out vec4 texC;

void main()
{
    mat4 mvpMatrix = projektionMatrix * viewMatrix * modelMatrix;
    gl_Position = mvpMatrix * vert;
    texC = texCoord;
}
