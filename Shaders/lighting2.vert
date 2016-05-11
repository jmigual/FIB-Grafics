#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

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

uniform mat3 normalMatrix;

uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space
uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient 
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse 
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

uniform vec3 boundingBoxMin; // cantonada minima de la capsa englobant 
uniform vec3 boundingBoxMax; // cantonada maxima de la capsa englobant

uniform vec2 mousePosition;  // coordenades del cursor (window space; origen a la cantonada inferior esquerra)

out vec4 frontColor;
out vec2 vtexCoord;

vec4 light(vec3 N, vec3 V, vec3 L)
{
 N=normalize(N); V=normalize(V); L=normalize(L);
 vec3 R = normalize(2.0*dot(N,L)*N - L);
 vec3 H = normalize(vec3(0,0,1) + L);  // V + L
 float NdotL = max(0.0, dot(N, L));
 float RdotV = max(0.0, dot(R, V));
 float NdotH = max(0.0, dot(N, H));
 float Idiff = NdotL;
 float Ispec = 0; 
 if (NdotL>0) Ispec=pow(RdotV, matShininess);
 return
 matAmbient * lightAmbient + 
 matDiffuse * lightDiffuse * Idiff +
 matSpecular * lightSpecular * Ispec;
}

void main()
{
    vec3 P = (modelViewMatrix*vec4(vertex, 1.0)).xyz;
    vec3 N = normalMatrix * normal;
    vec3 L = lightPosition.xyz - P; 
    vec3 V = -P;

    frontColor = light(N,V,L);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex.xyz, 1.0);
}
