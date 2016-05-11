#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat3 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform mat4 modelMatrixInverse;
uniform mat4 viewMatrixInverse;
uniform mat4 projectionMatrixInverse;
uniform mat4 modelViewMatrixInverse;
uniform mat4 modelViewProjectionMatrixInverse;

uniform float time;

uniform float amplitude = 0.1;
uniform float freq = 1; 
uniform float PI = 3.14159265359;

void main()
{ 
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex.xyz + normal*amplitude*sin(2*PI*freq*time), 1.0) ;
}
