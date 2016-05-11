#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	if (gl_PrimitiveIDIn == 0) {
      float R = length(boundingBoxMax - boundingBoxMin) / 2.0;
      vec3 C = (boundingBoxMax + boundingBoxMin) / 2.0;
      
      vec4 col = vec4(0, 1, 1, 1);
      vec4 pos;
      
      gfrontColor = col;
      pos = vec4(C.x - R, boundingBoxMin.y - 0.01, C.z + R, 1);
      gl_Position = modelViewProjectionMatrix * pos;
      EmitVertex();
      
      gfrontColor = col;
      pos = vec4(C.x - R, boundingBoxMin.y - 0.01, C.z - R, 1);
      gl_Position = modelViewProjectionMatrix * pos;
      EmitVertex();
      
      gfrontColor = col;
      pos = vec4(C.x + R, boundingBoxMin.y - 0.01, C.z + R, 1);
      gl_Position = modelViewProjectionMatrix * pos;
      EmitVertex();
      
      gfrontColor = col;
      pos = vec4(C.x + R, boundingBoxMin.y - 0.01, C.z - R, 1);
      gl_Position = modelViewProjectionMatrix * pos;
      EmitVertex();
      
      EndPrimitive();
	}
	
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0.);
		vec4 pos = gl_in[i].gl_Position;
		pos.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * pos;
		EmitVertex();
	}
    EndPrimitive();
    
    for( int i = 0 ; i < 3 ; i++ )
    {
        gfrontColor = vfrontColor[i];
        gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
