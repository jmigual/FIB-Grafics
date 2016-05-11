#version 330 core

in vec3 N;   
in vec3 V;
in vec3 P;
vec3 lights[4] = vec3[]( vec3(0, 10, 0), vec3(0, -10, 0), vec3(10, 0, 0), vec3(-10, 0, 0) );
vec3 lightsC[4] = vec3[]( vec3(0, 1, 0), vec3(1, 1, 0), vec3(0, 0, 1), vec3(1, 0, 0) );

uniform float time;
uniform bool rotate;

out vec4 fragColor;

// V, N, P, lightPos han d'estar al mateix espai de coordenades
// V és el vector unitari cap a l'observador
// N és la normal
// P és la posició 
// lightPos és la posició de la llum
// lightColor és el color de la llum
vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos, vec3 lightColor)
{
	const float shininess = 100.0;
	const float Kd = 0.5;
	N = normalize(N);
	vec3 L = normalize(lightPos - P);
	vec3 R = reflect(-L, N);
	float NdotL = max(0.0, dot(N,L));
	float RdotV = max(0.0, dot(R,V));
	float spec =  pow( RdotV, shininess);
	return vec4(Kd*lightColor*NdotL + vec3(spec),0);
}

void main()
{
	mat3 rot = mat3(1.0);
	if (rotate) rot = mat3( vec3(cos(time), sin(time), 0), vec3(-sin(time), cos(time), 0), vec3(0,0,1)); 
	
	vec4 c = vec4(.0,.0,.0,.0);
	for (int i = 0; i < lights.length(); ++i) {
      c += light(normalize(V),N,P, rot*lights[i], lightsC[i]);
	} 
	
	fragColor = c; 
}
  