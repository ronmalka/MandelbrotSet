#version 330 core
#define MAX_ITERATIONS 1000

in vec2 texCoord0;

uniform uint power;

int get_iterations()
{
    float constReal = (texCoord0.x - 0.5) * 4.0;
    float constImag = (texCoord0.y - 0.5) * 4.0;

    int iterations = 0;

    float real = 0.0;
    float imag = 0.0;
 
    while (iterations < MAX_ITERATIONS)
    {
        uint tmpPow = uint(1);
        float prevReal = real;
        float prevImag = imag;

        while(tmpPow<<1 < power){
            float tmpReal = real;
            real = (real * real - imag * imag);
            imag = (2.0 * tmpReal * imag);
            tmpPow = tmpPow<<1;
        }

        if(tmpPow != power){
            float tmpReal = real;
            real = (real * prevReal - imag * prevImag);
            imag = ( prevImag * tmpReal + prevReal * imag);
        }

        real += constReal;
        imag += constImag;

        float dist = real * real + imag * imag;
         
        if (dist > power*power)
            break;
 
        ++iterations;
    }
    return iterations;
}

vec4 return_color()
{
    int iter = get_iterations();
    if (iter == MAX_ITERATIONS)
    {
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
 
    float iterations = float(iter) / MAX_ITERATIONS;    
    return vec4(0.0f, iterations, 0.0f, 1.0f);
}
 
void main()
{
    int iter = get_iterations();
    if (iter == MAX_ITERATIONS)
    {
        gl_FragColor =  vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    else{
         float iterations = float(iter) / MAX_ITERATIONS;    
         gl_FragColor = vec4(0.0f, iterations, 0.0f, 1.0f);
    }
}
