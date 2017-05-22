#version 130
//default130.vert: a simple fragment shader

varying vec4 col;

void main()
{
    gl_FragColor = col;
}
