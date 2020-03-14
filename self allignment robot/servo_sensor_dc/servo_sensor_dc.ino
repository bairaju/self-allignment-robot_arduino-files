//Ultrasonic sensor+Dc motors +servo

#include <Servo.h>
#include <NewPing.h>

Servo name_servo;
int servo_position = 0;
int distance=20;
long duration,inches,cms;

const int triggerpin=9;
const int echopin=10;
const int input1=4;
const int input2=5;
const int input3=6;
const int input4=7;

void setup() 
{
  name_servo.attach(9);
  Serial.begin(9600); 
  pinMode (input1, OUTPUT);
  pinMode (input2, OUTPUT);
  pinMode (input3, OUTPUT);
  pinMode (input4, OUTPUT);
}
void loop() 
{
  for (servo_position =0;servo_position<=60;servo_position+=1)
  {
    name_servo.write(servo_position);
    delay(10);
  }
  for (servo_position=90;servo_position>=0;servo_position-=1)
  {
    name_servo.write(servo_position);
    delay(10);
  }
  if (distance >=20)
  {
  digitalWrite(input1,HIGH);
  digitalWrite(input2, LOW);
  digitalWrite(input3, HIGH);
  digitalWrite(input4, LOW);
  delay(2000);
  } 
  else if(servo_position>=30)
  //continue;
  {
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  digitalWrite(input3, LOW);
  digitalWrite(input4, HIGH);
  delay(2000);
  }
  else if(servo_position<=30)
  //continue;
  {
  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  digitalWrite(input3, HIGH);
  digitalWrite(input4, LOW);
  delay(2000);
  } 
  else if(distance<=20)
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
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Inches: ");
  Serial.println(inches);
  Serial.print("Centimeter: ");
  Serial.println(cms);
  }
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
