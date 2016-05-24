#version 330 core
in vec3 vertex; 

out vec2 vtexCoord; 

uniform mat4 modelViewProjectionMatrix; 
uniform float radius; 

void main() {	
    gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0); 
    vtexCoord = (4.0/radius)*(vertex.xy + vertex.zx); 
}
