/*
 * basic.pde - L293x H bridge library example Version 2.10
 * Copyright (c) 2012 Luis Sismeiro. All right reserved.
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
 * 20120115 Luis Sismeiro
 */
 
#include <L29x.h>

/*
 * Parameter 1: enable pin (used for PWM)
 * Parameter 2: motor pin
 * Parameter 3: motor pin
 */
L29x motor(3, 2, 4);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println("One line motor control");
  motor.rotPos(255); // fastest speed in one direction
  delay(2000);
  motor.stop();
  delay(1000);
  motor.rotNeg(160); // Slower speed backwards
  delay(2000);
  motor.stop();
  delay(1000);
  
  
  // Same function but with AF_Motor compatible commands
  Serial.println("Same function but with AF_Motor compatible commands");
  motor.run(FORWARD);
  motor.setSpeed(255); // fastest speed in one direction
  delay(2000);
  motor.run(BRAKE);    // Fast brake using "eletrical brake" from shortcurcuit the motor
  delay(1000);
  motor.run(BACKWARD);
  motor.setSpeed(160); // Slower speed backwards
  delay(2000);
  motor.stop();
  delay(1000);
  
  
  // Demonstartion of setMinimumSpeed to eliminate unuseful range in setSpeed
  Serial.println("setMinimumSpeed = 0 shows unused PWM range");
  
  motor.run(FORWARD);
  motor.setSpeed(0);
  motor.setMinimumSpeed(0);
  for (int i = 0; i <= 255; i++)
  {
    Serial.print("Speed =\t"); Serial.println(i,DEC);
    motor.setSpeed(i);
    delay(100); // Delay to be able to see the speedchange;  
  }
  for (int i = 255; i >= 0; i--)
  {
    Serial.print("Speed =\t"); Serial.println(i,DEC);
    motor.setSpeed(i);
    delay(100); // Delay to be able to see the speedchange;  
  }
  
  motor.run(BRAKE);    // Fast brake using "eletrical brake" from shortcurcuit the motor
  delay(3000);
  
  // Demonstartion of setMinimumSpeed to eliminate unuseful range in setSpeed
  Serial.println("setMinimumSpeed = 150 shows redusing of unused PWM range");
  
  motor.run(FORWARD);
  motor.setSpeed(150);
  motor.setMinimumSpeed(0);
  for (int i = 0; i <= 255; i++)
  {
    Serial.print("Speed =\t"); Serial.println(i,DEC);
    motor.setSpeed(i);
    delay(100); // Delay to be able to see the speedchange;  
  }
  for (int i = 255; i >= 0; i--)
  {
    Serial.print("Speed =\t"); Serial.println(i,DEC);
    motor.setSpeed(i);
    delay(100); // Delay to be able to see the speedchange;  
  }
  
  motor.run(BRAKE);    // Fast brake using "eletrical brake" from shortcurcuit the motor
  delay(3000);
  
  
  
  
}
