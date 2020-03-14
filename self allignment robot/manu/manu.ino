#include <Servo.h>
//Servo myservo; 
Servo servo1;   //base
Servo servo2;   //shoulder
Servo servo3;   //elbow
Servo servo4;   //wrist
Servo servo5;   //endeffector 1
Servo servo6;   //endeffector 2

//int myservo_position = 0; initially those are 0's
int servo_position1 = 0;
int servo_position2 = 0;
int servo_position3 = 0;
int servo_position4 = 0;
int servo_position5 = 0;
int servo_position6 = 0;

//Declaring lengths(l) and input values (x3,y3)
//x3,y3 delares at the end effector position
//here the l1 is shoulder
//l2 will be elbow
//l3 will be wrist
//int l1 = 5;
//int l2 = 5;
//int l3 = 5;
//int x3 = 50;
//int y3 = 60;

//wants to find distances r1,r2,r3
//for that we need the pi1,pi2,pi3
//after that find the angles theta1,theta2,theta3
//int r1 = 0;
//int r2 = 0;
//int r3 = 0;

void setup() {
  // put your setup code here, to run once:
  int l1 = 20;
  int l2 = 30;
  int l3 = 40;
  int x3 = 50;
  int y3 = 60;
  int r1;
  int r2;
  int r3;

  Serial.begin
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
