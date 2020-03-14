//Ultrasonic sensor+Dc motors +servo

#include <Servo.h>

//----------------------defining servos
Servo myservo; 
Servo five_servo;
Servo five_servo1;
Servo five_servo2;
Servo five_servo3;
Servo five_servo4;
int max_distance=60;

//------------------------defining sensor
const int triggerpin=9;
const int echopin=10;
const int input1=4;
const int input2=5;
const int input3=6;
const int input4=7;
//------------------------------------------------------

int myservo_position = 0; 
int servo_position = 0;
int servo_position1 = 0;
int servo_position2 = 0;
int servo_position3 = 0;
int servo_position4 = 0;
 
void setup() {
  //-----------------------------for sensors
  Serial.begin(9600); 
  pinMode (input1, OUTPUT);
  pinMode (input2, OUTPUT);
  pinMode (input3, OUTPUT);
  pinMode (input4, OUTPUT);
  //--------------------------------for servos
  myservo.attach(12);
  myservo.write(40);//set the fixed angle base servo
  five_servo.attach (6);
  five_servo1.attach(8);
  five_servo2.attach(9);
  five_servo3.attach(10);
  five_servo4.attach(11);
 //-----------------------------------------------------
}
 
void loop() {
  long duration,inches,cms;
  if(max_distance>=20)
  {
  digitalWrite(input1,HIGH);
  digitalWrite(input2, HIGH);
  digitalWrite(input3, HIGH);
  digitalWrite(input4, HIGH);
  delay(2000);
  }
  else if(max_distance==40)
  {
  digitalWrite(input3, LOW);
  digitalWrite(input4, LOW);
  delay(2000);
  for (servo_position = 0; servo_position <=90; servo_position +=1)
  {
 
    five_servo.write(servo_position);
    delay(10);
  }
  for (servo_position=90; servo_position >= 0; servo_position -=1){
 
    five_servo.write(servo_position);
    delay(10);
  }
  for (servo_position1 = 0; servo_position1 <=50; servo_position1 +=1)
  {
 
    five_servo1.write(servo_position1);
    delay(10);
  }
 
  for (servo_position1=50; servo_position1 >= 0; servo_position1 -=1)
  {
 
    five_servo1.write(servo_position1);
    delay(10);
  }
  for (servo_position2 = 0; servo_position2 <=50; servo_position2 +=1)
  {
 
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
  for (servo_position3=50; servo_position3 >= 0; servo_position3 -=1)
  {
 
    five_servo3.write(servo_position3);
    delay(10);
  }
  for (servo_position4 = 0; servo_position4 <=50; servo_position4 +=1)
  {
 
    five_servo4.write(servo_position4);
    delay(10);
  }
  for (servo_position4=50; servo_position4 >= 0; servo_position4 -=1)
  {
 
    five_servo4.write(servo_position4);
    delay(10);
  }
  }
  else
  {
  pinMode(triggerpin,OUTPUT);
  digitalWrite(triggerpin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin,HIGH);
  delayMicroseconds(15);
  digitalWrite(triggerpin,LOW);
  pinMode(echopin,INPUT);
  duration=pulseIn(echopin,HIGH);
  inches=microsecondsToInches(duration);
  cms=microsecondsToCentimeters(duration);
  max_distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(max_distance);
  Serial.print("Inches: ");
  Serial.println(inches);
  Serial.print("Centimeter: ");
  Serial.println(cms);
  }
}
long microsecondsToInches(long microseconds)
{
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}

//----------------------------------------------------------------------------
  
