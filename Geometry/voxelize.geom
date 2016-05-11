#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vN[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform mat4 modelViewProjectionMatrix;

uniform float time;

uniform float step = .2;

const float dx[] = float[](  1,  1, -1, -1,  -1, -1, -1, -1,  -1, -1,  1,  1,   1,  1,  1,  1 ); 
const float dy[] = float[]( -1,  1, -1,  1,  -1,  1, -1,  1,  -1,  1, -1,  1,  -1,  1, -1,  1 ); 
const float dz[] = float[](  1,  1,  1,  1,   1,  1, -1, -1,  -1, -1, -1, -1,  -1, -1,  1,  1 );

void main( void )
{    
    vec3 B = vec3(0,0,0);
    for (int i = 0; i < 3; ++i) B += gl_in[i].gl_Position.xyz; 
    B /= 3.0; 
    B = vec3(B.x - mod(B.x, step), B.y - mod(B.y, step), B.z - mod(B.z, step));
     
    gfrontColor = vec4(.3,.3,.3,1);
    // Strip llarg
    for (int i = 0; i < 16; ++i) {
      gl_Position = modelViewProjectionMatrix * vec4(B.x + dx[i]*step/2, B.y + dy[i]*step/2, B.z + dz[i]*step/2, 1);
      EmitVertex();
    } 
    EndPrimitive();  
    
    // Tapes
    gl_Position = modelViewProjectionMatrix * vec4(B.x + step/2, B.y + step/2, B.z - step/2, 1);
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(B.x + step/2, B.y + step/2, B.z + step/2, 1);
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(B.x - step/2, B.y + step/2, B.z - step/2, 1);
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(B.x - step/2, B.y + step/2, B.z + step/2, 1);
    EmitVertex(); 
    EndPrimitive();
    
    gl_Position = modelViewProjectionMatrix * vec4(B.x + step/2, B.y - step/2, B.z - step/2, 1);
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(B.x + step/2, B.y - step/2, B.z + step/2, 1);
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(B.x - step/2, B.y - step/2, B.z - step/2, 1);
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(B.x - step/2, B.y - step/2, B.z + step/2, 1);
    EmitVertex();
    EndPrimitive();
}
