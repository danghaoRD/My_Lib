/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Low Pass
Filter model: Butterworth
Filter order: 8
Sampling Frequency: 10 KHz
Cut Frequency: 0.100000 KHz
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
z = 0.918080 + j -0.024742
z = 0.918080 + j 0.024742
z = 0.949536 + j -0.059627
z = 0.949536 + j 0.059627
z = 0.984780 + j -0.031883
z = 0.984780 + j 0.031883
z = 0.986574 + j -0.065286
z = 0.986574 + j 0.065286
***************************************************************/
#define Ntap 31

#define DCgain 524288

__int16 fir(__int16 NewSample) {
    __int16 FIRCoef[Ntap] = { 
        14600,
        15035,
        15448,
        15838,
        16203,
        16543,
        16855,
        17139,
        17393,
        17616,
        17807,
        17967,
        18094,
        18189,
        18254,
        18311,
        18254,
        18189,
        18094,
        17967,
        17807,
        17616,
        17393,
        17139,
        16855,
        16543,
        16203,
        15838,
        15448,
        15035,
        14600
    };

    static __int16 x[Ntap]; //input samples
    __int32 y=0;            //output sample
    int n;

    //shift the old samples
    for(n=Ntap-1; n>0; n--)
       x[n] = x[n-1];

    //Calculate the new output
    x[0] = NewSample;
    for(n=0; n<Ntap; n++)
        y += FIRCoef[n] * x[n];
    
    return y / DCgain;
}
