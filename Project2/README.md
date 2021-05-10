

Industrial Automation

Project #2: T-RECS Discrete-Time (D.T.) Controller Implementation

Due: See Canvas ”Assignments”

For this project, you will implement a Discrete-Time (D.T.) Controller, via emulation, on

the T-RECS. You will be emulating your Continuous-Time (C.T.) controller from Project#1,

but you may decided to go back and update the controller if you would like. You will also

present all of that in a report form (written in Latex).

Your report should include, but not limited to, the following aspects:

• Report Writing

– Tell a good story

– Quality Figures

– Take Pride in your work

– There should be a suﬃcient amount of information and directions so that someone

can replicate this work

• Emulation

– You will emulate your C.T. controller, from Project#1, using Euler’s Forward

Method. Show the derivation out. Make sure the ﬁlter is stable before imple-

menting.

– You will also emulate your C.T. controller, from Project#1, using Tustin’s Method.

You can use c2d() for this one if you like.

– You will explain, theoretically, what is emulation, why is one emulation better

than another, and show the derivation of Euler’s Forward Method.

• Simulink Implementation #1

– Unlike the last project, you will not use “auto” for the solver (technically the

emulation scheme), and you will choose “ode1” and implement again.

– You will explain the process of choosing a “solver” in simulink and why you would

choose one solver over another. Remember that you are writing this report so that

others can recreate this work (you, preferably, when you pick this report up in a

few years).

• Simulink Implementation #2

– In this part, you will not let Simulink do the emulation for you and instead, use

the D.T. Transfer-Function (T.F.) block and use the coeﬃcients that you found

via Euler’s Forward Method.

1





– Same thing as above but this time implement the ﬁlter that you found via Tustin’s

approximation.

– Compare the two experimental results (given that we are sampling pretty fast,

they could be very similar)

• Arduino Due Implementation

– You will need to convert your C(z), that you got via Tustin’s method, into code

(use either Direct Method 1 or 2 that I taught you).

– Now you will implement your code on the Arduino IDE. Here are some pointers:

∗ You will need access to the Timers on the Due (to know when 1 milisecond

has passed and you should run your controller code). You will need to the

Install “DueTimer” Library by Ivan Seidel. You can do that via the “Manage

Libraries” menu option on the Arduino IDE.

∗ See the DueTimer documentation for some important details:

https://github.com/ivanseidel/DueTimer

∗ You will especially want to read about how to set up an interrupt and how

to use the Arduino Servo Library along with the DueTimer library.

∗ Check out the T-RECS PID sample code to get an idea of the structure that

your code should have.

∗ Your actual Controller code should be placed inside of an an Interrupt-

Service-Routine (ISR)

• Quadrature Encoder as the Feedback Sensor

– Set all the appropriate registers on the Due so that the Quadrature Decoder is

function.

– Use the Encoder as feedback and Implement the Arduino code.

– Compare the Potentiometer sensor reading to the Encoder Sensor Reading and

see if it has an aﬀect on the controller implementation.

• References

• Appendices (for example, code portions or derivations that you think shouldn’t be in

the body of the report but should be in the appendices).

2


