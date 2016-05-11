#version 330 core
layout (location = 0) in vec3 vertex;

uniform mat4 modelViewProjectionMatrix;

uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

void main(void)
{
    vec3 v = vertex * (boundingBoxMax-boundingBoxMin);
    v += boundingBoxMin;
    gl_Position = modelViewProjectionMatrix * vec4(v, 1);
}

