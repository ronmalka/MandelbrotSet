#version 330 core
#define MAX_ITERATIONS 100
#define SENSITIVITY 0.02
#define CENTER 0.5

in vec2 texCoord0;

uniform sampler2D sampler;
uniform uint power;
uniform uint colors;
uniform float zoom;
uniform float offset_x;
uniform float offset_y;

int numOfIterations()
{
    int iterations = 0;
    float constReal = ((texCoord0.x -CENTER - offset_x*SENSITIVITY)*zoom)* 4.0;
    float constImag = ((texCoord0.y -CENTER - offset_y*SENSITIVITY)*zoom)* 4.0;
    float real = 0.0;
    float imag = 0.0;
 
    while (iterations++ < MAX_ITERATIONS)
    {
        uint tmpPow = uint(1);
        float prevReal = real;
        float prevImag = imag;

        while(tmpPow<<1 <= power){
            float tmpReal = real;
            real = (real * real - imag * imag);
            imag = 2.0 * tmpReal * imag;
            tmpPow = tmpPow<<1;
        }
        while(tmpPow != power){
            float tmpReal = real;
            real = (real * prevReal - imag * prevImag);
            imag = ( prevImag * tmpReal + prevReal * imag);
            tmpPow++;
        }
        real += constReal;
        imag += constImag;

        float dist = real * real + imag * imag;
         
        if (dist > 2*2)
            break;
    }
    return iterations;
}

 
void main()
{
    int iter = numOfIterations();
    if (iter == MAX_ITERATIONS)
    {
        gl_FragColor =  vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    else{
         float colorScale = float(iter) / MAX_ITERATIONS;
         float requestedColor = floor(colorScale*colors)/colors;    
	     gl_FragColor = texture2D(sampler, vec2(requestedColor,1.0));
    }
}
