

Industrial Automation

Project Ts: Sampling and Reconstruction Demonstration

For this assignment you will be writing a report (using Latex) to explain the Shannon

Sampling Theorem (also attributed to Nyquist (see wiki page)) using an example signal as

demonstration.

Your report should include, but not limited to, the following aspects:

• Pretend that you are writing this to an engineer who is not familiar with the nuances

of the Shannon Sampling Thm. Therefore, your text should clearing explain what’s

going on and you should use equations and ﬁgures (that you make yourself) to explain.

Examples demonstrating what you’re describing in words are going to be a crucial way

of clearing presenting the topic in a palatable way.

• Reference any equations you don’t derive.

• All ﬁgures and plots should be created by you. So no ﬁgures or images from google.

• You will demonstrate the reconstruction, xR(t), of a continuous-time signal ,x(t), from

∗

the sampled signal x (t) = x(kT ) = x[k]. You will show and describe, by using text

and ﬁgures, that aliasing will occur if you don’t sample fast enough.

s

• The signal you will use for your demonstration is x(t) = sin(2πt) + 0.2cos(12πt).

• The sampling rates you will use will be

\1. Ts = 0.17 seconds. Make sure to explain (text and ﬁgures, so think about the

ﬁgures I drew on the board to describe this process) why this is too slow and

how it produces aliasing. Verify that your estimate of the aliasing frequency is

approximately what results from the demo.

\2. Ts = 0.017 seconds. Make sure to explain (text and ﬁgures) why this is too slow

and how it produces aliasing.

• One issue that we need to overcome is that there is no such thing as “continuous” in

Matlab. So we will use a very small time increment, ∆T = .0001 seconds, to represent a

“continuous” signal and then we will “sample” using a multiple of that time increment

(T = N ∆T, where N is an integer greater than 1). The following code will plot the

s

s

s

continuous signal and start your matlab program:

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%

%

%

%

%

My\_Reconstruction

by

Shalom Ruben

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all

clc

1





close all

DT = .0001; %DT is not the sampling rate! It is the "continuous" rate

t = -20:DT:20; %but you can feel free to zoom in later,

%so the reader can better visualize.

%But do keep t from -20 to 20 even if you only

%view the date from -5 to 5 (for example)

%when you plot this, it should look "continuous"

plot(t,x,’linewidth’,2)

• The next step is to build the sampled signal x[k]. This is done by deciding Ts is, and

therefore what Ns is also, and then making everything, but those samples, equal to

zero. Depending how how you’re doing the convolution, it may be useful that the new

vector x[k] includes all the zeros in between the non-zero samples for the convolution

process later.

• The next step is the Reconstruction of the original signal. You will explain and demon-

strate that xR(t) = x(t) under certain conditions and otherwise they will not be equal.

• As you will explain, using text, ﬁgures, and equations, you must pass the sampled

data through a low-pass ﬁlter to produce xR(t). One way to do this is to do it in

the frequency-domain and the other is to do it in the time-domain via convolution

of x∗(t) and h(t) where h(t) is the impulse response of the low-pass ﬁlter (actually

pulse-response since the input to the low-pass ﬁlter was discrete) that you are passing

the signal through. In this report you will show the results using the following four

low-pass ﬁlters:

\1. Ideal Low-Pass Filter (ILP)

\2. Zero-Order-Hold (ZOH)

\3. Non-causal First-Order-Hold (FOH)

\4. causal Predictive FOH (PFOH)

• In class we derived the pulse-response (h(t)) for the ZOH, ILP, and FOH, but you need

to show the derivation of the impulse response of the PFOH.

• You must create (build the vector) for each impulse response (corresponding to each

low-pass ﬁlter) and take care to make sure that you are using the time-increment ∆T

(so think continuous) to produce them or the convolution will not be correct.

• Only use Matlab’s |conv()|function to get the reconstructed signal after passing x∗(t)

through the low-pass ﬁlter.

• I derived in class the Frequency-Response-Function (FRF) ( which is also the Fourier

Transform of the pulse-response h(t)) of the ZOH, so you should use that to plot the

the FRF (magnitude only) of that and compare it to the FRF of an ILP and discuss.

You should also derive the FRF of the FOH and also plot that, magnitude only, on

the same plot and discuss why FOH is better than ZOH but not better than ILP.

• You should also weave in the idea of sampling many times greater than the minimum

2





sampling rate and what beneﬁts you can draw from the frequency domain perspective.

• Remember that you are not limited to just these bullet points and you should tell a

coherent and interesting story.

3


