/*
 * L29x.cpp - L29x H bridge library Version 3.00
 * Copyright (c) 2013 Johnny Nilsson. All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Originaly created by 20120115 Luis Sismeiro
 * 20130817 Johnny Nilsson
 * 20130818 Sebastian Nilsson
 *
 */
 
 /*
 
 
Hi guys! After some day, I finally managed to change the PWM frequency of all PWM pins of my Arduino Mega 2560.
All the explanations are foundamentally here:
http://usethearduino.blogspot.com/2008/11/changing-pwm-frequency-on-arduino.html
In this brief article the author explains very clearly how to change some values in Arduino Diecimila registers, in order to enhance the PWM frequency.
Here I simply modified a little bit the author'code to make it match with Arduino 2560.
Here follows my brief instructions and descriptions!

1) Arduino 2560 has 12 pins supporting PWM. They are from 2 to 13 included.

2) the PWM default frequency is 490 Hz for all pins, with the exception of pin 13 and 4,
whose frequency is 980 Hz (I checked with an oscilloscope).

3) In order to change frequency on pin 'A', we have to change some value in the timer
(or register), controlling pin 'A'. This is the list of timers in Arduino Mega 2560:

timer 0 (controls pin 13, 4);
timer 1 (controls pin 12, 11);
timer 2 (controls pin 10, 9);
timer 3 (controls pin 5, 3, 2);
timer 4 (controls pin 8, 7, 6);

As you can see, a given timer controls more than one pin (every change about a timer will affect all pins depending on it!).

4) You can access a timer simply changing in your code (tipically in the setup()), the value of variable TCCRnB, where 'n' is the number of register. So, if we want  to change the PWM frequency of pins 10 and 9,  we will have to act on TCCR2B .

5) The TCCRnB is a 8 bit number.  The first three bits (from right to left!) are called CS02, CS01, CS00, and they are the bits we have to change.
Those bits in fact represent an integer number (from 0 to 7) called 'prescaler' , that Arduino uses to generate the frequency for PWM.

6) First of all, we have to clear these three bits, i.e they must be all set to 0:

int myEraser = 7;             // this is 111 in binary and is used as an eraser
TCCR2B &= ~myEraser;   // this operation (AND plus NOT),  set the three bits in TCCR2B to 0

7) now that CS02, CS01, CS00  are clear, we write on them a new value:

int myPrescaler = 3;         // this could be a number in [1 , 6]. In this case, 3 corresponds in binary to 011.   
TCCR2B |= myPrescaler;  //this operation (OR), replaces the last three bits in TCCR2B with our new value 011

smiley-cool now we have a new PWM frequency on pin 9 and 10!


I registered those values on all PWM pins, changing the value of prescaler (the only exception are pins 13 and 14, see later):

prescaler = 1 ---> PWM frequency is 31000 Hz
prescaler = 2 ---> PWM frequency is 4000 Hz
prescaler = 3 ---> PWM frequency is 490 Hz (default value)
prescaler = 4 ---> PWM frequency is 120 Hz
prescaler = 5 ---> PWM frequency is 30 Hz
prescaler = 6 ---> PWM frequency is <20 Hz

(prescalers equal t 0  or 7 are useless).

Those prescaler values are good for all timers (TCCR1B, TCCR2B, TCCR3B, TCCR4B) except for timer 0 (TCCR0B). In this case the values are:

prescaler = 1 ---> PWM frequency is 62000 Hz
prescaler = 2 ---> PWM frequency is 7800 Hz
prescaler = 3 ---> PWM frequency is 980 Hz (default value)
prescaler = 4 ---> PWM frequency is 250 Hz
prescaler = 5 ---> PWM frequency is 60 Hz
prescaler = 6 ---> PWM frequency is <20 Hz

Note that timer 0 is the one on which rely all time functions in Arduino: i.e., if you change this timer, function like delay() or millis() will continue to work but at a different timescale (quicker or slower!!!)

Ok, I hope it will help!
Cheers, Valerio 



 L29x Arduino Library
--------------------
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

	L29x motorOne(3, 2, 4);  ( pin3 is the PWM=EnableA, pin 2 is IN1, pin 4 is IN2 ==> Controls MotorA )
	L29x motorTwo(6, 7, 8);  ( pin6 is the PWM=EnableB, pin 7 is IN3, pin 8 is IN4 ==> Controls MotorB )

That's it for the setup part. Then we use the methods available:

	stop() - 1,2A with zero, 1A and 2A LOW 
	rotPos(byte pwm) - 1,2A with PWM, 1A LOW and 2A HIGH
	rotNeg(byte pwm) - 1,2A with PWM, 1A HIGH and 2A LOW

For example, to start the motors fast in one direction:
	
	motorOne.rotPos(255);
	motorTwo.rotPos(255);

To stop both motors:

	motorOne.stop();
	motorTwo.stop();	
	
Added functionality that is compatible with AF_Motor library
=================================================================================================================================================
motorOne.run(FORWARD)  Set direction of the motor.
motorOne.run(BACKWARD) Set direction of the motor.
motorOne.run(RELEASE)  Freewheel the motor without any eletrical brake of the motor. Sets Motorspeed = 0. (= MotorOne.setSpeed(0);)
motorOne.run(BRAKE)    (Not implemented in AF_Motor). Shorts the motor to create eletrical brake. Sets Motorspeed = 0. (= MotorOne.setSpeed(0);)


motorOne.setSpeed( byte pwm) Sets the speed of the motor from 0 to 255.
motorOne.run(FORWARD)/motorOne.run(BACKWARD) combined with motorOne.setSpeed(255) is eqvivalent to motorOne.rotPos(255)/motorOne.negPos(255)
	
motorOne.getSpeed() Get the speed of the motor from 0 to 255.
All speed commands are saved in a private variable ( byte _currentPwm; ). Returns the current speed of the motor.

motorOne.setMinimumSpeed(byte pwm) Set the lowest pwm where the motor starts working and adjust the setSpeed(0) to start from lowest working pwm




	
	
That's it, I hope you find this library useful in your own sketches.	
	
20120114 Luis Sismeiro
20130817 Johnny Nilsson
20130818 Sebastian Nilsson

 
 */
 
 
#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

#include "L29x.h"

L29x::L29x(byte enable, byte pin1, byte pin2) {
  _currentPwm = 0;
  _minimumSpeed = 0;
  _enable = enable;
  _pin1 = pin1;
  _pin2 = pin2;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}  

void L29x::stop()
{
  _currentPwm = 0;
  analogWrite(_enable, 0);
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
}

void L29x::rotPos(byte pwm)
{
  _currentPwm = pwm;
  analogWrite(_enable, pwm);
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, HIGH);
}

void L29x::rotNeg(byte pwm)
{
  _currentPwm = pwm;
  analogWrite(_enable, pwm);
  digitalWrite(_pin1, HIGH);
  digitalWrite(_pin2, LOW);
}

// AF Motor compatible functions
void L29x::run(uint8_t cmd) {
	switch (cmd) {
	  case FORWARD:
	    analogWrite(_enable, _currentPwm);
        digitalWrite(_pin1, HIGH);
        digitalWrite(_pin2, LOW);
		break;
	  case BACKWARD:
		analogWrite(_enable, _currentPwm);
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, HIGH);
		break;
	  case RELEASE:
	    // Free running motor Stop = Slow Motor Stop is done when Enable = LOW and NOT PWM
		// and pin1/pin2 = Dont Care 
	    _currentPwm = 0;
		digitalWrite(_enable,LOW);
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
		break;
	  case BRAKE: 
	    // Fast motor Stop = Brake is done when Enable = HIGH and NOT PWM
		// and pin1 is equal pin2.
		// pin1 = Pin2 = LOW. Equal with RELEASE. Differance is that Enable is HIGH
	    _currentPwm = 0;
		digitalWrite(_enable,HIGH);
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
		break;
  }
}

// 
void L29x::setSpeed(uint8_t speed) {
    // Map the speed to motors working PWM to aviod individual motors unusable PWM range from 0 to "lowestPWM where the motor starts"
    if (speed == 0)
    	_currentPwm = 0;
    else	
	    _currentPwm = map(speed,0,255,_minimumSpeed,255);
	analogWrite(_enable, _currentPwm);
}
// set speed in percentage from -100 to 100
void L29x::setSpeedPercentage(float speed) {
	// anothing above 100 or below -100 is invalid
	if (speed > 100)
		speed = 100;
	else if (speed < -100)
		speed = -100;
	
	// negative speed	
	if (speed > 0) {
		run(FORWARD);
		setSpeed((uint8_t) (255/100 * speed));
	}
	else if (speed < 0){
		run(BACKWARD);
		setSpeed((uint8_t) (-255/100 * speed));
	}
	else {
		setSpeed((uint8_t) 0);
	}
}

uint8_t L29x::getSpeed(void) {
    // Simply return the privat _currentPwm that holds the latest setSpeed.
	return _currentPwm;
}

void L29x::setMinimumSpeed(uint8_t minimumSpeed) {
    // Set individual motors unusable PWM range from 0 to "lowestPWM where the motor starts"
	_minimumSpeed = minimumSpeed;	
}
