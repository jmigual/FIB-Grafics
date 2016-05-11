#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float amplitude = 0.1;
uniform float freq = 1;
uniform float PI = 3.14159265359;
uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4( N.z ) ;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex.xyz + normal*amplitude*sin(2*PI*freq*time + 2*PI*texCoord.s) , 1.0);
}
