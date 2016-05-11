#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

vec4 white = vec4(.8);
vec4 black = vec4(vec3(0.0),1.0);

uniform float n = 8;

float diff = .1;

void main()
{
    vec2 V = vtexCoord*n;
    
    vec4 color = white;
    if (abs(floor(V.x) - V.x) <= diff || abs(floor(V.y) - V.y) <= diff) color = black;
    fragColor = color; 
}
 