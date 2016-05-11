#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

vec2 C = vec2(.5,.5);

void main()
{
    float L = length(vtexCoord - C);
    float val = step(.2, L);
    fragColor = vec4(1, val, val, 1);
}
