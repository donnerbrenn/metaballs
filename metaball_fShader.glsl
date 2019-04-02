uniform int vCount;

uniform vec2 vectors[1023];


vec3 hsv2rgb(vec3 c) {

//  c.r=min(c.r,1.0);

  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec4 hsvColored(float value)
{
    vec3 input;
    vec3 output;

    input.x=((value));
    input.y=1,0;
    input.z=1.0;

    output=hsv2rgb(input);
    return(vec4(output,1));
}

vec4 rgbColored(float value)
{
    vec4 output = vec4(vec3(value,0,0),1);
    if(output.r<3.5)
        output.r=0;

    return output;
}


void main()
{
    float value=0;
    vec2 currentFrag=gl_FragCoord-1;
    currentFrag/=2560;

    for(int i=0;i<vCount;i++)
    {
        value+=.75/length((vectors[i]/2560)-currentFrag),0,1;
    }
    value/=vCount;
    gl_FragColor = rgbColored(value);
}
