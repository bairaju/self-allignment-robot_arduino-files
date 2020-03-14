

#include <Servo.h>

//Servo myservo; 
Servo five_servo;
Servo five_servo1;
Servo five_servo2;
Servo five_servo3;
Servo five_servo4;

//int myservo_position = 0; 
int servo_position = 0;
int servo_position1 = 0;
int servo_position2 = 0;
int servo_position3 = 0;
int servo_position4 = 0;
 
void setup() {

 // myservo.attach(12);
  //myservo.write(40);//set the fixed angle base servo
  five_servo.attach (6);
  five_servo1.attach(8);
  five_servo2.attach(9);
  five_servo3.attach(10);
  five_servo4.attach(11);
 
  
 
}
 
void loop() {
 
  for (servo_position = 0; servo_position <=90; servo_position +=1){
 
    five_servo.write(servo_position);
    delay(10);
  }
 
  for (servo_position=90; servo_position >= 0; servo_position -=1){
 
    five_servo.write(servo_position);
    delay(10);
  }
   for (servo_position1 = 0; servo_position1 <=50; servo_position1 +=1){
 
    five_servo1.write(servo_position1);
    delay(10);
  }
 
  for (servo_position1=50; servo_position1 >= 0; servo_position1 -=1){
 
    five_servo1.write(servo_position1);
    delay(10);
  }
   for (servo_position2 = 0; servo_position2 <=50; servo_position2 +=1){
 
    five_servo2.write(servo_position2);
    delay(10);
  }
 
  for (servo_position2=50; servo_position2 >= 0; servo_position2 -=1){
 
    five_servo2.write(servo_position2);
    delay(10);
  }
  for (servo_position3 = 0; servo_position3 <=50; servo_position3 +=1){
 
    five_servo3.write(servo_position3);
    delay(10);
  }
  for (servo_position3=50; servo_position3 >= 0; servo_position3 -=1){
 
    five_servo3.write(servo_position3);
    delay(10);
  }
   for (servo_position4 = 0; servo_position4 <=50; servo_position4 +=1){
 
    five_servo4.write(servo_position4);
    delay(10);
  }
  for (servo_position4=50; servo_position4 >= 0; servo_position4 -=1){
 
    five_servo4.write(servo_position4);
    delay(10);
  }
}
