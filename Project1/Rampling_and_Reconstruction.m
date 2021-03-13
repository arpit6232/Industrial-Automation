clear all;
close all;
clc;

% Time domain
tStart = -20;
tStep  = 0.0001;
tEnd   = 20;

% Sampling period
Ts = 0.017;

t      = tStart:tStep:tEnd;

% Original signal
x = @(t)(sin(2*pi*t) + 0.2*cos(12*pi*t));

%Ideal low pass filter 
ilpl        = @(t) sinc((t-tStart-1)/Ts);

%Ideal low pass filter fft
ilpl_fft        = @(t) fftshift(fft(sinc((t)/Ts)));

% Impulse ZOH 
zohImpl     = @(t,Ts) rectangularPulse(0,Ts,t-tStart);

% Impulse ZOH fft
zohImpl_fft     = @(t,Ts) fftshift(fft(rectangularPulse(t/Ts)));

% Impulse FOH
fohImpl     = @(t,Ts) triangularPulse((t-tStart-1)/Ts);

% Impulse FOH fft
fohImpl_fft     = @(t,Ts) fftshift(fft(triangularPulse((t)/Ts)));

% Impulse FOH predictive
fohPreImp   = @(t,Ts) (rectangularPulse((t-tStart)/Ts - 1/2) - ...
                            rectangularPulse((t-tStart)/Ts - 3/2) + ...
                             triangularPulse((t-tStart)/Ts - 1));
                         
% Impulse FOH predictive fft
fohPreImp_fft   = @(t,Ts) fftshift(fft((rectangularPulse((t)/Ts - 1/2) - ...
                            rectangularPulse((t)/Ts - 3/2) + ...
                             triangularPulse((t)/Ts - 1))));
                         
% Samples
nSamples = (tEnd-tStart)/Ts; 
samples  = 0:nSamples;

% Sampled signal
xSampled = zeros(1,length(t));
xSampled(1:Ts/tStep:end) = x(samples*Ts);                            
                         
tt = -1:1e-4:1;                       
figure(1);
subplot(4,1,1);
plot(tt,ilpl(tt),"DisplayName","Ideal Low pass filter");
grid on; box on; axis tight;
ylabel("Ideal Low pass filter");
xlabel("time");

subplot(4,1,2);
plot(tt,zohImpl(tt,Ts),"DisplayName","Zero Order Hold");
grid on; box on; axis tight;
ylabel("Zero Order Hold");
xlabel("time");

subplot(4,1,3);
plot(tt,fohImpl(tt,Ts),"DisplayName","First Order Hold");
grid on; box on; axis tight;
ylabel("First Order Hold");
xlabel("time");

subplot(4,1,4);
plot(tt,fohPreImp(tt,Ts),"DisplayName","Predictive First Order Hold");
grid on; box on; axis tight;  
ylabel("Predictive First Order Hold");
xlabel("time");

tt = -1:1e-4:1;                       
figure(1);
subplot(4,1,1);
plot(tt,ilpl_fft(tt),"DisplayName","Ideal Low pass filter");
grid on; box on; axis tight;
ylabel("Ideal Low pass filter");
xlabel("time");

subplot(4,1,2);
plot(tt,zohImpl_fft(tt,Ts),"DisplayName","Zero Order Hold");
grid on; box on; axis tight;
ylabel("Zero Order Hold");
xlabel("time");

subplot(4,1,3);
plot(tt,fohImpl_fft(tt,Ts),"DisplayName","First Order Hold");
grid on; box on; axis tight;
ylabel("First Order Hold");
xlabel("time");

subplot(4,1,4);
plot(tt,fohPreImp_fft(tt,Ts),"DisplayName","Predictive First Order Hold");
grid on; box on; axis tight;  
ylabel("Predictive First Order Hold");
xlabel("time");

% % Convolution with impulse response
xILPL        = conv(ilpl(t),xSampled);
xZoh         = conv(zohImpl(t,Ts),xSampled);
xFoh         = conv(fohImpl(t,Ts),xSampled);
xFohPreImp   = conv(fohPreImp(t,Ts),xSampled);
% 

xILPL        = xILPL(1:length(t));
xZoh         = xZoh(1:length(t));
xFoh         = xFoh(1:length(t));
xFohPreImp   = xFohPreImp(1:length(t));

% Plot
figure(2);
hold all;
subplot(6,1,1);
plot(t,x(t),"DisplayName","Input Signal");
ylabel("Magnitude");
xlabel("time");
title("Input Signal");

subplot(6,1,2);
plot(t,xSampled, "DisplayName","Sampled Signal");

subplot(6,1,3);
plot(t,xILPL,'r',"DisplayName","Ideal Low pass filter");
ylabel("Magnitude");
xlabel("time");
title("Reconstructed Signal, Ideal Low pass Filter");

subplot(6,1,4);
plot(t,xZoh,'r',"DisplayName","Zero Order Hold");
ylabel("Magnitude");
xlabel("time");
title("Reconstructed Signal, Zero Order Hold");
   
subplot(6,1,5);
plot(t,xFoh,'r',"DisplayName","First Order Hold");
ylabel("Magnitude");
xlabel("time");
title("Reconstructed Signal, First Order Hold");

subplot(6,1,6);
plot(t,xFohPreImp,"DisplayName","Impulse Predictive FOH predictive");
ylabel("Magnitude");
xlabel("time");
title("Reconstructed Signal, Predictive First Order Hold");