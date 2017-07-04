# CarND-Controls-PID

The goal of this project is to implement a PID controller to drive a car in the simulator without leaving the drivable
portion of the track surface. Bottom line the car must drive safely around the lap track.

The main task of this project is to identify the P, I and D parameters to control the steering angle so that the car 
can drive around the track. The optimization method used in this project to find the PID parameters is Twiddle.

## Finding the P, I and D parameters

The Twiddle optimization method implemented in this project uses the average Cross-Track Error (CTE) as optimization 
cost while trying to find the best values of P, I and D.

The Twiddle method is implemented in the class Twiddle. It is setup to run for 1000 steps in the track before restarting 
and running with new values of P, I and D until the sum of dp values converge to a value less than a given tolerance
(0.2 in this project).

The throttle during the optimization was set up as a linear function of the steering angle, so that large absolute
steering angle values would lead to a reduced throttle:

throttle = 0.4 - 0.39 * fabs(steering);

The following command line invokes the PID Controller in optimization mode (Twiddle):

./pid 1

The best values found for the PID Controller are:
* P: 2.96113
* I: 0.0
* D: 4.32024

To run the PID Controller with those values one can use the following command line:

./pid

### P: Proportional coefficient
The P coefficient guides the steering angle to compensate for the CTE. If used alone it would normally lead to the car to
overshoot the position where CTE is zero.

### I: Integral coefficient
The I coefficient handles systematic bias, compensating for alignment differences between the steering angle and the 
direction the car takes. Since in the simulator there is no systematic bias, i.e. the steering and the direction of the
 car are aligned, it makes sense that the optimizer found an Integral coefficient of zero.
 
### D: Differential coefficient
The D coefficient guides the steering angle to avoid overshooting once the CTE reaches zero.


## Conclusion
The PID Controller implemented in this project can drive safely around the track, reaching speeds close to 30MPH.


