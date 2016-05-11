#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n;

void main()
{
    int y = int(gl_FragCoord.y);
    if (n != 0 && y%n != 0) discard;
    
    fragColor = frontColor;
}
