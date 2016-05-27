#version 330 core
uniform mat4 modelViewProjectionMatrix;
uniform float factor = 1.0;

in vec3 vertex;
out vec2 pos;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);
    gl_Position.y *= factor;
    
    pos = vertex.xz;
}

