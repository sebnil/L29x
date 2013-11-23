## L29x Arduino Library
![L298n](http://sebastiannilsson.com/wp-content/uploads/2013/11/l298n-arduino-library-300x224.jpg)

http://sebastiannilsson.com/en/blogg/arduino-bibliotek-for-motordrivare-l29x

This is a library to simplify the use of H bridges in you sketches. You
need to configure the Arduino pins that are connected to the H bridge
according to their functions.

For example we connect an L293 driving two motors to the Arduino Uno.
This are the pins used:

	L293 ------------- Arduino
	--------------------------
	1,2EN ------------ 2
	1A --------------- 3 (PWM) 
	2A --------------- 4
	3,4EN ------------ 6 (PWM)
	3A --------------- 7
	4A --------------- 8

We start declaring the two motors:
```cpp
	L29x motorOne(3, 2, 4);  ( pin3 is the PWM=EnableA, pin 2 is IN1, pin 4 is IN2 ==> Controls MotorA )
	L29x motorTwo(6, 7, 8);  ( pin6 is the PWM=EnableB, pin 7 is IN3, pin 8 is IN4 ==> Controls MotorB )
```
That's it for the setup part. Then we use the methods available:
```cpp
	stop() - 1,2A with zero, 1A and 2A LOW 
	rotPos(byte pwm) - 1,2A with PWM, 1A LOW and 2A HIGH
	rotNeg(byte pwm) - 1,2A with PWM, 1A HIGH and 2A LOW
```
For example, to start the motors fast in one direction:
```cpp	
	motorOne.rotPos(255);
	motorTwo.rotPos(255);
```
To stop both motors:
```cpp
	motorOne.stop();
	motorTwo.stop();	
```	
To control the motor with percentage
```cpp
	setSpeedPercentage(float speedInPercentage);
	For example setSpeedPercentage(-50); will run the motor at 50% torque in the backward direction.
```
### Added functionality that is compatible with AF_Motor library
```cpp
motorOne.run(FORWARD)  Set direction of the motor.
motorOne.run(BACKWARD) Set direction of the motor.
motorOne.run(RELEASE)  Freewheel the motor without any eletrical brake of the motor. Sets Motorspeed = 0. (= MotorOne.setSpeed(0);)
motorOne.run(BRAKE)    (Not implemented in AF_Motor). Shorts the motor to create eletrical brake. Sets Motorspeed = 0. (= MotorOne.setSpeed(0);)

motorOne.setSpeed( byte pwm) Sets the speed of the motor from 0 to 255.
motorOne.run(FORWARD)/motorOne.run(BACKWARD) combined with motorOne.setSpeed(255) is eqvivalent to motorOne.rotPos(255)/motorOne.negPos(255)
	
motorOne.getSpeed() Get the speed of the motor from 0 to 255.
All speed commands are saved in a private variable ( byte _currentPwm; ). Returns the current speed of the motor.

motorOne.setMinimumSpeed(byte pwm) Set the lowest pwm where the motor starts working and adjust the setSpeed(0) to start from lowest working pwm
```

That's it, I hope you find this library useful in your own sketches.	
	
* 20120114 Luis Sismeiro (http://usethearduino.blogspot.com/2008/11/changing-pwm-frequency-on-arduino.html)
* 20130817 Johnny Nilsson
* 20130818 Sebastian Nilsson (http://sebastiannilsson.com/en/blogg/arduino-bibliotek-for-motordrivare-l29x)

 
 
