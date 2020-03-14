#include <Servo.h>  // add servo library

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
// create servo object to control a servo


void setup() {
  PinMode(A0,INPUT);
  PinMode(3,OUTPUT);
  servo1.attach(3);
  
  PinMode(A1,INPUT);
  PinMode(4,OUTPUT);
  servo2.attach(4);
  
  Pinmode(A2,INPUT);
  PinMode(5,OUTPUT);
  servo3.attach(5);
  
  Pinmode(A3,INPUT);
  PinMode(6,OUTPUT);
  servo4.attach(6);
  Serial.begin(9600);
 
}
void loop() {
   val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
   val = map(val, 180, 1023, 0, 90);     // scale it to use it with the servo (value between 0 and 180)
   myservo.write(val);                  // sets the servo position according to the scaled value
   delay(15);                           // waits for the servo to get there
}
