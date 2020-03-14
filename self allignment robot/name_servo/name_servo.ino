#include <Servo.h>
 
Servo name_servo;
 
int servo_position = 0;
 
void setup() {
 
  name_servo.attach (5);
 
}
 
void loop() {
 
  for (servo_position = 0; servo_position <=110; servo_position +=1){
 
    name_servo.write(servo_position);
    delay(30);
  }
 
  for (servo_position=60; servo_position >= 0; servo_position -=1){
 
    name_servo.write(servo_position);
    delay(30);
  }
}
