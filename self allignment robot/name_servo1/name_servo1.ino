
#include <Servo.h>
Servo servoMain; 

void setup()
{
   servoMain.attach(9);
}

void loop()
{
   servoMain.write(45);  // Turn Servo Left to 45 degrees
   delay(10);          // Wait 1 second
   servoMain.write(0);   // Turn Servo Left to 0 degrees
   delay(10);          // Wait 1 second
   servoMain.write(90);  // Turn Servo back to center position (90 degrees)
   delay(10);          // Wait 1 second
   servoMain.write(135); // Turn Servo Right to 135 degrees
   delay(1000);          // Wait 1 second
   servoMain.write(180); // Turn Servo Right to 180 degrees
   delay(1000);          // Wait 1 second
   servoMain.write(90);  // Turn Servo back to center position (90 degrees)
   delay(1000);          // Wait 1 second   
}
