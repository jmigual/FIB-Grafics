#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D explosion;
uniform float time;
uniform float fps = 30;

void main()
{
    int frame = int(trunc(time*30)); 
    
    fragColor = texture(explosion, vec2(frame/8.0 + vtexCoord.s/8, (-1-frame/8 + vtexCoord.t)/6)); 
    fragColor *= fragColor.a;
}
 