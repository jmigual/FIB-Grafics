#version 330 core

out vec4 fragColor;
in vec4 frontColor;
in vec2 vtexCoord;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2; 

void main()
{
    vec4 r = texture(rock1, vtexCoord);
    vec4 g = texture(grass2, vtexCoord);
    vec4 n = texture(noise0, vtexCoord);
    fragColor = mix(r,g,n);
}
