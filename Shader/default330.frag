#version 450
//#extension GL_ARB_separate_shader_objects : enable
// default330.frag: a simple fragment shader
//
// notes:
// GL_ARB_separate_shader_objects is not needed for version >= 410

layout(location = 0)in vec4 col;
layout(location = 0)out vec4 fragColor;

void main()
{
    //fragColor = col;
    fragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
