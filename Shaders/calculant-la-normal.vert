#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

out vec3 V;
out vec3 C;

void main()
{
    V = (modelViewMatrix*vec4(vertex,1.0)).xyz;
    C = color;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
