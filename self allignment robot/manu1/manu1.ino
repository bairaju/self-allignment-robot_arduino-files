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
//int l1 = 20;
//int l2 = 30;
//int l3 = 40;
//int x3 = 50;
//int y3 = 60;

//wants to find distances r1,r2,r3
//for that we need the pi1,pi2,pi3
//after that find the angles theta1,theta2,theta3
//int r1 = 0;
//int r2 = 0;
//int r3 = 0;

 int l1 = 20;
  int l2 = 30;
  int l3 = 40;
  int x3 = 50;
  int y3 = 60;
  int z3 = 120;
  
  int pi1;
  int pi2;
  int pi3;
  
  int r1;
  int r2;
  int r3;
  int ang1;
  int ang2;
  int ang3;
  
  int a = x3*x3;
  int b = y3*y3;
  int c = sq(l3) - sq(l2) - sq(r3);
  int d = sq(r3) - sq(l2) - sq(l3);

void setup() {
  Serial.begin(9600);

  Serial.print("finding r1= ");
  r1 = sqrt(a+b);
  Serial.println(r1);
  delay(1000);
  Serial.print("finding r2= ");
  r2 = z3 - l1;
  Serial.println(r2);
  delay(1000);
  Serial.print("finding r3= ");
  r3 = sqrt(sq(r1) + sq(r2));
  Serial.println(r3);
  delay(1000);

  Serial.print("finding pi1= ");
  pi1 = acos(c / -2 * l2 * r3);
  Serial.println(pi2);
  delay(1000);
  Serial.print("finding pi2= ");
  pi2 = atan(r2 / r1);
  Serial.println(pi1);
  delay(1000);
  Serial.print("finding pi3= ");
  pi3 = acos(d / -2 * l2 * l3);
  Serial.println(pi3);
  delay(1000);

  Serial.print("finding angle1= ");
  ang1 = atan(y3 / x3);
  Serial.println(ang1);
  delay(1000);
  Serial.print("finding angle2= ");
  ang2 = pi2 - pi1;
  Serial.println(ang2);
  delay(1000);
  Serial.print("finding angle3= ");
  ang3 = 180 - pi3;
  Serial.println(ang3);
  delay(1000);

  // myservo.attach(12);
  //myservo.write(40);//set the fixed angle base servo
  servo1.attach(6);
  servo2.attach(8);
  servo3.attach(9);
  servo4.attach(10);
  servo5.attach(11);
  servo6.attach(7);

  servo2.write(ang1);
  servo3.write(ang2);
  servo4.write(ang3);
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
