#version 330 core

in vec4 frontColor;
in vec3 vnormal;
out vec4 fragColor;

void main()
{
    fragColor = frontColor * normalize(vnormal).z; 
}
