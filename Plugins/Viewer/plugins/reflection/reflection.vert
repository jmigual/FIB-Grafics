#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform mat3 normalMatrix;

uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space

uniform vec3 boundingMin;
uniform vec3 boundingMax;
uniform float radius;

uniform float factor = 1.0;
uniform bool texture;

out vec2 pos;
out vec3 N, V, L;

void main()
{
    vec4 paux = vec4(vertex,1.0);
    paux.y -= boundingMin.y;
    paux.y *= factor;
    paux.y += boundingMin.y;
    
    if (texture) {
        paux.y = boundingMin.y;
        paux.x *= radius;
        paux.z *= radius;
        pos.x = (vertex.x + 1.)/2.;
        pos.y = (vertex.z + 1.)/2.;
    }
    else {
        vec3 P = (modelViewMatrix*vec4(vertex, 1.0)).xyz;
        N = normalMatrix * normal;
        L = lightPosition.xyz - P; 
        V = -P;
    }
    gl_Position = modelViewProjectionMatrix * paux;
}

