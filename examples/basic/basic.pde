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
}

void loop()
{
  motor.rotPos(255); // fastest speed in one direction
  delay(2000);
  motor.stop();
  delay(1000);
  motor.rotNeg(160); // fastest speed in the other direction
  delay(2000);
  motor.stop();
  delay(1000);
}
