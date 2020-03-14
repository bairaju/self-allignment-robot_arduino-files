#include <Servo.h>
 
Servo name_servo;
 
int servo_position = 0;
 
void setup() {
 
  name_servo.attach (6);
 
}
 
void loop() {
 
  for (servo_position = 0; servo_position <=50; servo_position +=1){
 
    name_servo.write(servo_position);
    delay(10);
  }
 
  for (servo_position=70; servo_position >= 0; servo_position -=1){
 
    name_servo.write(servo_position);
    delay(10);
  }
}
