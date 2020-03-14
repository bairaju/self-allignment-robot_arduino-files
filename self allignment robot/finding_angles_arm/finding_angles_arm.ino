 #include <Servo.h>
 //Servo myservo; 
 Servo five_servo;
 Servo five_servo1;
 Servo five_servo2;
 Servo five_servo3;
 Servo five_servo4;
 Servo five_servo5;
//int myservo_position = 0; 
 int servo_position = 0;
 int servo_position1 = 0;
 int servo_position2 = 0;
 int servo_position3 = 0;
 int servo_position4 = 0;
 int servo_position5 = 0;
  int l1 = 1.5;
  int l2 = 5.2;
  int l3 = 4.3;
  int x3 = 50;
  int y3 = 20;
  int z3 = 40;
  
  int pi1;
  int pi2;
  int pi3;
  
  int r1;
  int r2;
  int r3;
  int ang1;
  int ang2;
  int ang3;
  
  int a = sq(x3);
  int b = sq(y3);
  int c = sq(l3) - sq(l2) - sq(r3);
  int d = sq(r3) - sq(l2) - sq(l3);
  int e = sq(r1) ;
  int f = sq(r2);
 void setup() {
  // put your setup code here, to run once:
  //five_servo == user defined
  //five_servo1 == angl1 value
  //five_servo2 == angl2 value
  //five_servo3 == angl3 value
  //five_servo4 == gripper
  //five_servo5 ==gripper 1
  
  five_servo.attach (7);
  five_servo1.attach(8);
  five_servo2.attach(9);
  five_servo3.attach(10);
  five_servo4.attach(11);
  five_servo5.attach(12);
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
  r3 = sqrt(e+f);
  Serial.println(r3);
  delay(1000);

  Serial.print("finding pi1= ");
  //pi1 = acos(int(c / -(2 * l2 * r3)));
  pi1 = acos(c / -(2 * l2 * r3));
  Serial.println(pi2);
  delay(1000);
  Serial.print("finding pi2= ");
  //pi2 = atan(int(r2 / r1));
  pi2 = atan(r2 / r1);
  Serial.println(pi1);
  delay(1000);
  Serial.print("finding pi3= ");
  //pi3 = acos(int(d / -(2 * l2 * l3)));
  pi3 = acos(d / -(2 * l2 * l3));
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
  
  five_servo.write(60);
  five_servo1.write(ang1);
  five_servo2.write(ang2);
  five_servo3.write(ang3);
}
void loop() {
  // put your main code here, to run repeatedly:
  five_servo5.write(160);
  delay(2000);
  five_servo5.write(10);
  delay(2000);

  five_servo4.write(10);
  delay(2000);
  five_servo5.write(10);
  delay(2000);

  five_servo.write(90);
  five_servo1.write(-(ang1));
  five_servo2.write(-(ang2));
  five_servo3.write(-(ang3));
  delay(1000);
  
  five_servo4.write(150);
  five_servo5.write(150);
  delay(2000);

  five_servo.write(110);
  five_servo1.write(ang1);
  five_servo2.write(ang2);
  five_servo3.write(ang3);

}
