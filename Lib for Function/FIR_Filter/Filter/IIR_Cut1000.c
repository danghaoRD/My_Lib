/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Low Pass
Filter model: Butterworth
Filter order: 8
Sampling Frequency: 10 KHz
Cut Frequency: 1.000000 KHz
Coefficents Quantization: 16-bit

Z domain Zeros
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000

Z domain Poles
z = 0.480940 + j -0.065552
z = 0.480940 + j 0.065552
z = 0.575287 + j -0.337794
z = 0.575287 + j 0.337794
z = 0.605365 + j -0.270397
z = 0.605365 + j 0.270397
z = 0.730497 + j -0.521030
z = 0.730497 + j 0.521030
***************************************************************/
#define NCoef 8
#define DCgain 8192

__int16 iir(__int16 NewSample) {
    __int16 ACoef[NCoef+1] = {
          403,
         3224,
        11286,
        22573,
        28216,
        22573,
        11286,
         3224,
          403
    };

    __int16 BCoef[NCoef+1] = {
         2048,
        -9798,
        21391,
        -27561,
        22792,
        -12339,
         4258,
         -854,
           76
    };

    static __int32 y[NCoef+1]; //output samples
    //Warning!!!!!! This variable should be signed (input sample width + Coefs width + 8 )-bit width to avoid saturation.

    static __int16 x[NCoef+1]; //input samples
    int n;

    //shift the old samples
    for(n=NCoef; n>0; n--) {
       x[n] = x[n-1];
       y[n] = y[n-1];
    }

    //Calculate the new output
    x[0] = NewSample;
    y[0] = ACoef[0] * x[0];
    for(n=1; n<=NCoef; n++)
        y[0] += ACoef[n] * x[n] - BCoef[n] * y[n];

    y[0] /= BCoef[0];
    
    return y[0] / DCgain;
}
