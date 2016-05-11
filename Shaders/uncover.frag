#version 330 core

in vec4 frontColor;
in float x;
in float w;
out vec4 fragColor;

uniform float time;

void main()
{
    if (x / w > time - 1) discard;
    fragColor = vec4(0,0,1,1);  
}
