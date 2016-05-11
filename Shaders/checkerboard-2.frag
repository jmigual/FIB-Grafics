#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

vec4 white = vec4(.8);
vec4 black = vec4(vec3(0.0),1.0);

uniform float n = 8;

void main()
{
    ivec2 c = ivec2(floor(vtexCoord*(int(n)))); 
    vec4 color = vec4(1.);
    if ((c.x + c.y)%2 == 0) color = white;
    else color = black;
    fragColor = color;
}
