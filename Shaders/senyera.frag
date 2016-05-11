#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

vec4 white = vec4(vec3(1,1,0),1);
vec4 black = vec4(vec3(1,0,0),1.0);

uniform float n = 9;

float diff = .1;

void main()
{
    vec2 V = vtexCoord*n;
    
    ivec2 c = ivec2(trunc(vtexCoord*(int(n)))); 
    vec4 color = white;
    if ((c.x)%2 != 0 && c.x < 9 && c.x > -9) color = black;
    fragColor = color;
}
 