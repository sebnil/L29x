/*
 * L29x.h - L29x H bridge library Version 3.00
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
 

 
 
 */
 
#ifndef L29X_H
#define L29X_H

#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

// AF motor Compatible defines
// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3      // Function defined in AF_Motor but not implemented
#define RELEASE 4                                                                                          


class L29x
{
  public:
    L29x(byte enable, byte pin1, byte pin2);
	void stop();
	void rotPos(byte pwm);
    void rotNeg(byte pwm);
	
	// AF Motor Compatible functions
	void run(uint8_t);
    void setSpeed(uint8_t);
	void setSpeedPercentage(float);
	
	// Not implemented in AF_Motor, but adds functionality to AF_Motor functions
	uint8_t getSpeed(void);
	void setMinimumSpeed(uint8_t);
	
  private:
    byte _currentPwm;
	byte _minimumSpeed;
    byte _enable;
	byte _pin1;
	byte _pin2;
};

#endif