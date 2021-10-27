%*********************************************************************/
% Freeware Demo SW from the www.dsp-weimich.com                      */
% Version 1.0                                                        */
% FIR_Filter.m                                                       */
% Octave Script                                                      */
% High-level interactive language for numerical computations         */
% Support the article: FIR filters                                   */
%*********************************************************************/
close all
clear all
clc all

pkg load control
pkg load signal

%---------------------
% FIR Low Pass Filter
% Calculation on the http://t-filter.engineerjs.com/
% Method: Parks-McClellan
% Fs=12kHz
% Pass Band: 0Hz ...1kHz with max    3dB (requirement) => really +(0,75...2)dB
% Stop Band: 2kHz...6kHz with min  -40dB (requirement) => really -41,03dB
% Order 17
fir_coeff_original = [-0.013303717505109074 -0.022915393927793015 -0.02681670506036818 -0.01215698212279612 0.028324189273488634 0.09154991631606571 0.16236182127129264 0.21837630790224832 0.2396940621588613 0.21837630790224832 0.16236182127129264 0.09154991631606571 0.028324189273488634 -0.01215698212279612 -0.02681670506036818 -0.022915393927793015 -0.013303717505109074];
coeff_norm = 10^(0.7525133982943817/20); % -0.7521dB
fir_coeff = fir_coeff_original/coeff_norm;
%fir_coeff = fir_coeff_original;
F_sample_in_Hz = 12e3;
%---------------------
coeff_shift_factor = 17;
scale_factor = 2^coeff_shift_factor;

% Plotting the FIR Filter Magnitude Response
% Input parameters:
% fir_coefficients - FIR coefficients / Impulse Response
% FsampleInHz - Sampling Frequency in Hz
function FirFilterResponse(fir_coefficients, FsampleInHz, StringName)
   FIR_ORDER = length(fir_coefficients);
   F_range_in_Hz = 1:int32(FsampleInHz/2);
   Tsample_in_seconds = 1/FsampleInHz;
   FreqMatrix = zeros(FIR_ORDER,F_range_in_Hz);
   for index = 1:FIR_ORDER
      for freq = F_range_in_Hz
         FreqMatrix(index,freq) = e^(-2*j*pi*freq*Tsample_in_seconds*(index-1));
      end
   end
   SpectrumValues = fir_coefficients*FreqMatrix;
   dig_func_dmr=20*log10(abs(SpectrumValues));
   %max(dig_func_dmr)
   # -----
   # Magnitude Response
   figure();
   %semilogx(F_range_in_Hz,dig_func_dmr);
   plot(F_range_in_Hz,dig_func_dmr);
   grid;
   title (strcat(StringName," FIR Filter Magnitude Response filter"));
   xlabel ("Frequency in Hz");
   ylabel ("dB");
   # -----
   yticks("manual");
   y_user=10:-10:min(yticks);
   yticks(y_user);
   ylim("manual");
   ylim([min(dig_func_dmr) 2*max(dig_func_dmr)]);
   # -----
   dig_func_angle=unwrap(arg(SpectrumValues));
   # -----
   # Phase Response
   figure();
   plot(F_range_in_Hz,dig_func_angle*(180/pi));
   grid;
   title (strcat(StringName," FIR Filter Phase Response filter"));
   xlabel ("Frequency in Hz");
   ylabel ("Phase in degrees");
   xticks("manual");
   x_user=0:1000:int32(FsampleInHz/2);
   xticks(x_user);
   xlim("manual");
   xlim([0 int32(FsampleInHz/2)]);
   yticks("manual");
   angle_minimum = 1.1*min(dig_func_angle*(180/pi));
   y_user=90:-30:angle_minimum;
   yticks(y_user);
   ylim("manual");
   ylim([angle_minimum 0]);
endfunction

% FIR Filter: FFT convolution with the Overlap-Add Method
% Input parameters:
% fir_coefficients - FIR coefficients / Impulse Response
% x_input - input data
% fft_size - FFT number=2^k
% Output parameters:
% y_output - FIR filter output
function y_output = FirFilter_FftConvolutionOverlapAdd(fir_coefficients, x_input, fft_size, StringName)
   x_block = fft_size - length(fir_coefficients) + 1;
   block_nmb = fix(length(x_input)/x_block);
   y_output = zeros(1, length(x_input)+length(fir_coefficients)-1);
   h_fft = fft(fir_coefficients,fft_size);
   for current_index = 0:(block_nmb-1)
      y_fft = fft(x_input(1+x_block*current_index:x_block*(current_index+1)),fft_size);
      y_block = ifft(h_fft.*y_fft,fft_size);
      y_output(1+x_block*current_index:x_block*current_index+fft_size)=y_output(1+x_block*current_index:x_block*current_index+fft_size)+y_block;
   end
   rest_value = mod(length(x_input),x_block);
   if (rest_value != 0)
      y_fft = fft(x_input(1+x_block*block_nmb:end),fft_size);
      y_block = ifft(h_fft.*y_fft,fft_size);
	  rest_size = length(y_output(1+x_block*block_nmb:end));
      y_output(1+x_block*block_nmb:end)=y_output(1+x_block*block_nmb:end)+y_block(1:rest_size);
   end
   figure();
   x_space = [1:length(x_input)];
   plot(x_space,x_input,x_space,y_output(x_space));
   grid;
   title (strcat(StringName," FIR Filter Input/Output"));
   xlabel ("nTs");
   ylabel ("Unit");
   xlim("manual");
   xlim([0 length(x_input)]);
   yticks("manual");
   y_user=20:-5:min(yticks);
   yticks(y_user);
   ylim("manual");
   signal_minimum = 1.1*min([min(x_input) min(y_output)]);
   signal_maximum = 1.1*max([max(x_input) max(y_output)]);
   ylim([signal_minimum signal_maximum]);
endfunction

% FIR Filter Coefficients Quantization
% Input parameters:
% fir_coefficients - FIR coefficients / Impulse Response
% ScaleFactor - integer scale
% Output parameters:
% fir_quantization - integer format
function fir_quantization = FirFilterQuantization(fir_coefficients, ScaleFactor)
   fir_quantization = ScaleFactor*fir_coefficients;
   fir_quantization = int32(fir_quantization);
   fir_quantization = double(fir_quantization);
   % fir_quantization =  fir_quantization/ScaleFactor;
endfunction

% Integer Test Signal to File
% Support C-Code
% Input parameters:
% SignalAmpl - amplitude of the test signal
% SignalFreqInHz - frequency of the test signal in Hz
% SignalLength - table length
% FsampleInHz - sampling frequency in Hz
% FileNameString - output file name
% Output parameters:
% TestSignal - test signal vector
function TestSignal = IntegerTestSignals2file(SignalAmpl, SignalFreqInHz, SignalLength, FsampleInHz, FileNameString)
   TestSignal = int32(SignalAmpl*sin(2*pi*(SignalFreqInHz/FsampleInHz)*[0:SignalLength-1]));
   fileDescriptor = fopen(FileNameString, 'wt');
   for index = 0:SignalLength-2
     if(mod(index,10) == 0)
        fprintf(fileDescriptor, "\n        ");
     end
     fprintf(fileDescriptor, "%6d, ", TestSignal(index+1));
   end
   % Last number without comma
   if(mod(SignalLength-1,10) == 0)
      fprintf(fileDescriptor, "\n        ");
   end
   fprintf(fileDescriptor, "%6d\n", TestSignal(end));
   fclose(fileDescriptor);
endfunction

% Integer Table to File
% Support C-Code
% Input parameters:
% ParameterVector - data array
% FileNameString - output file name
function IntegerParamVector2file(ParameterVector, FileNameString)
   nmb_in_line = 10;
   IntegerParameterVector = int32(ParameterVector);
   fileDescriptor = fopen(FileNameString, 'wt');
   for index = 0:length(IntegerParameterVector)-2
     if(mod(index,nmb_in_line) == 0)
        fprintf(fileDescriptor, "\n        ");
     end
     fprintf(fileDescriptor, "%6d, ", IntegerParameterVector(index+1));
   end
   % Last number without comma
   if(mod(length(IntegerParameterVector)-1,nmb_in_line) == 0)
      fprintf(fileDescriptor, "\n        ");
   end
   fprintf(fileDescriptor, "%6d\n", IntegerParameterVector(end));
   fclose(fileDescriptor);
endfunction

% Float Table to File
% Support C-Code
% Input parameters:
% ParameterVector - data array
% FileNameString - output file name
function FloatParamVector2file(ParameterVector, FileNameString)
   nmb_in_line = 5;
   fileDescriptor = fopen(FileNameString, 'wt');
   for index = 0:length(ParameterVector)-2
     if(mod(index,nmb_in_line) == 0)
        fprintf(fileDescriptor, "\n        ");
     end
     fprintf(fileDescriptor, "%9f, ", ParameterVector(index+1));
   end
   % Last number without comma
   if(mod(length(ParameterVector)-1,nmb_in_line) == 0)
      fprintf(fileDescriptor, "\n        ");
   end
   fprintf(fileDescriptor, "%9f\n", ParameterVector(end));
   fclose(fileDescriptor);
endfunction

% Processing
% ----------
% FIR Filter Coefficients in integer format
fir_coeff_q = FirFilterQuantization(fir_coeff,scale_factor);

% Variant1: Filter Response Plot
% --------------------------------
% % FIR Filter Coefficients in double format
% FirFilterResponse(fir_coeff, F_sample_in_Hz, "Double Coefficients: 17 order, Low Pass");

% FIR Filter Coefficients in integer format
FirFilterResponse(fir_coeff_q/scale_factor, F_sample_in_Hz, "Integer Coefficients: 17 order, Low Pass");

% % Variant2: Filter Response Plot
% % --------------------------------
% % FIR Filter Coefficients in double format
% [h, w] = freqz(fir_coeff,[1],256,F_sample_in_Hz);
% figure();
% freqz_plot(w, h);

% % FIR Filter Coefficients in integer format
% [h_q, w_q] = freqz(fir_coeff_q/scale_factor,[1],256,F_sample_in_Hz);
% figure();
% freqz_plot(w_q, h_q);

% Test Signals
Amplitude1=10;
freq_f1_Hz=500;
Amplitude2=10;
freq_f2_Hz=2000;
Xspace=[0:200];
Signals_f1 = Amplitude1*sin(2*pi*(freq_f1_Hz/F_sample_in_Hz)*Xspace);
Signals_f2 = Amplitude2*sin(2*pi*(freq_f2_Hz/F_sample_in_Hz)*Xspace);
SignalSum = Signals_f1 + Signals_f2;
SignalStep = 10*[ones(1,200)];

% FIR Filter Input=TestSignals/Output
y_output1 = FirFilter_FftConvolutionOverlapAdd(fir_coeff_q/scale_factor, Signals_f1, 32, "Input: Sinus f=0.5kHz");
y_output2 = FirFilter_FftConvolutionOverlapAdd(fir_coeff_q/scale_factor, Signals_f2, 32, "Input: Sinus f=2kHz");
y_output3 = FirFilter_FftConvolutionOverlapAdd(fir_coeff_q/scale_factor, SignalSum,  32, "Input: Sinus f=0.5kHz and f=2kHz");
y_output4 = FirFilter_FftConvolutionOverlapAdd(fir_coeff_q/scale_factor, SignalStep, 32, "Input: Step Signal");

% Generate the file with the test signal. Support the C-Code.
% Sinus, Amlitude=16383, Frequency 500Hz, Length 100 samples, Sampling Frequency 12kHz
testSignal1 = IntegerTestSignals2file(16383, 500, 100, 12000, "test_signal1.txt");

% Generate the file with the test signal. Support the C-Code.
% Sinus, Amlitude=16383, Frequency 2000Hz, Length 100 samples, Sampling Frequency 12kHz
testSignal2 = IntegerTestSignals2file(16383, 2000, 100, 12000, "test_signa2.txt");

% Generate the file with the test signal. Support the C-Code.
% testSignal1 + testSignal2
IntegerParamVector2file(testSignal1+testSignal2, "test_signa3.txt");

% Generate the file with the float FIR coefficients. Support the C-Code.
% Low Pass FIR Filter 17 order, Fband= 1000Hz, Sampling Frequency 12kHz
FloatParamVector2file(fir_coeff, "Order17_FirCoeffFloat.txt");

% Generate the file with the integer FIR coefficients. Support the C-Code.
% Low Pass FIR Filter 17 order, Fband= 1000Hz, Sampling Frequency 12kHz
IntegerParamVector2file(fir_coeff_q,"Order17_FirCoeffInteger.txt");

% Generate the file with the FIR coefficient shift factor. Support the C-Code.
IntegerParamVector2file(coeff_shift_factor,"FirCoeffShiftFactor.txt");
