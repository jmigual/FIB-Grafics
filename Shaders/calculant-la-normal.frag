#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 V;
in vec3 C;

void main()
{
    vec3 vX = dFdx(V);
    vec3 vY = dFdy(V);
    vec3 N = normalize(cross(vX, vY));
    fragColor = vec4(C,1.0)*N.z;
}
