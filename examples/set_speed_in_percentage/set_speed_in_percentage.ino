/* This example shows how to set motor speed in percentage where a negative
   value will run the motor backwards.
   This is very usuful in control applications. For example the output
   from a PID controller is most often a float and can be integrated with
   this library easily. 
*/
#include <L29x.h>
L29x motorLeft(9, 22, 23); // enable (PWM), motor pin 1, motor pin 2
L29x motorRight(8, 24, 29); // enable (PWM), motor pin 1, motor pin 2

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  motorLeft.setSpeedPercentage(-12.34);
  motorRight.setSpeedPercentage(-10);      
  delay(3000);
  motorLeft.setSpeedPercentage(100);
  motorRight.setSpeedPercentage(90);      
  delay(3000);
}

