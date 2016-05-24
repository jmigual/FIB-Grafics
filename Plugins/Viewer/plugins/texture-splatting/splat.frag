#version 330 core

uniform sampler2D sampler0; 
uniform sampler2D sampler1; 
uniform sampler2D sampler2;

in vec2 vtexCoord; 
out vec4 fragColor; 

void main() { 
    
    vec4 r = texture(sampler0, vtexCoord);
    vec4 g = texture(sampler1, vtexCoord);
    vec4 n = texture(sampler2, vtexCoord);
    fragColor = mix(r,g,n); 

}
