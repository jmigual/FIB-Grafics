 #version 330 core
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float SIZE;
uniform float time;

void main()
{
    vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
    float a = 1.0/SIZE;

    vec2 pos = st + 0.01*vec2(sin(10.0*time + 30.0*st.s));
    
    vec4 col = texture(colorMap, pos);
    
    /*
    vec4 sum=vec4(0.0);
    float count = 0.0;
    for (int i=-W; i<W; ++i)
    for (int j=-W; j<W; ++j)
    {
        vec4 tmp = texture(colorMap, st+vec2(a*float(i), a*float(j)));
        if (length(tmp.rgb)>0.0) // assumes background is black 
        {
            float w = max(0.0, float(W) - length(vec2(float(i), float(j))));
            count += w;
            sum += w*tmp;
        } 
    }
    sum /= count;
    sum = pow(sum, vec4(5.0));
    
    */
    
        
    fragColor = col;
}

