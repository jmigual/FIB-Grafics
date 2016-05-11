#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

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

vec4 red = vec4(1,0,0,1);
vec4 yellow = vec4(1,1,0,1);
vec4 green = vec4(0,1,0,1);
vec4 cian = vec4(0,1,1,1);
vec4 blue = vec4(0,0,1,1);

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    
    float yMin = -1.0;
    float yMax = 1.0;
    float y = (gl_Position.y/gl_Position.w);
    float yi = (y - yMin)/(yMax - yMin);
    
    if (yi < .25) frontColor = mix(red, yellow, yi / .25); 
    else if (yi < .5) frontColor = mix(yellow, green, (yi - .25)/.25);
    else if (yi < .75) frontColor = mix(green, cian, (yi - .5)/.25);
    else frontColor = mix(cian, blue, (yi - .75)/.25);
    vtexCoord = texCoord;
}
