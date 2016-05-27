#version 330 core
out vec4 fragColor;
in vec2 pos;

uniform sampler2D colorMap;

void main()
{    
    vec4 col = texture(colorMap, pos);
    fragColor = col;
}

