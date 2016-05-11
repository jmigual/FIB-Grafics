#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vN[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform mat4 modelViewProjectionMatrix;

uniform float time;

const float speed = .5;

void main( void )
{    
    vec3 N = vec3(0,0,0);
    for (int i = 0; i < 3; ++i) N += vN[i];
    N /= 3.0; 
    //N = normalize(N);
     
    for( int i = 0 ; i < 3 ; i++ ) 
    {
        gfrontColor = vfrontColor[i];
        vec4 pos = gl_in[i].gl_Position;
        pos += speed*time*vec4(N, 0.0);
        
        gl_Position = modelViewProjectionMatrix * pos;
        EmitVertex(); 
    } 
    EndPrimitive();
}
