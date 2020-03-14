//Ckt for the code of 6Dof

#include <Servo.h>

#define no_of_fields 6

Servo base; //s1
Servo shoulder; //s2
Servo foreArm; //s3
Servo wristFlex; //s4
Servo wristRotate; //s5
Servo claw; //s6

int inCommand[no_of_fields];
int ledPin=13;

void EchoData(int echoWord[])
{
   Serial.print("*");
 float total;
 for (int i = 0; i < no_of_fields; i++)
 {
  Serial.print((int)echoWord[i]); 
  total+= inCommand[i];
  Serial.print(",");
 }
 Serial.print((int)total);
 Serial.print(",");
 Serial.print("*");
 Serial.print("&");
}
void ClearOldData(int oldData[])
{
 for (int i = 0; i < no_of_fields; i++)
 {
  oldData[i] = 0;
 }
}

/* build 6DOF*/

void setup() 
{
  Serial.begin(38400);

  base.attach(3);
  shoulder.attach(4);
  foreArm.attach(5);
  wristFlex.attach(6);
  wristRotate.attach(7);
  claw.attach(8);

  //initialise all arms 
  base.write(20);      // 0 - 100, 20
  shoulder.write(30);  // 30 - 180, 30
  foreArm.write(10);   // 0 - 100, 10
  wristFlex.write(40); // 0 - 150, 40
  wristRotate.write(0);  // 0 - 180, 0
  claw.write(130);       // 90 - 140, 

  pinMode(ledPin,OUTPUT);
}
void demo()
{
 //initialise all arms
 for(int i = 20; i < 70; i += 1)
 {
   base.write(i);      // 시계반대방향. 0 - 100, 20
   delay(50);
 }
 for(int j = 70; j > 20; j -= 1)
 {
   base.write(j);      // 시계반대방향. 0 - 100, 20
   delay(50); 
 }

 for(int i = 30; i < 70; i += 1)
 {
   shoulder.write(i);  // 30 - 180, 30
   delay(50);
 }
 for(int j = 70; j > 30; j -= 1)
 {
   shoulder.write(j);  // 30 - 180, 30
   delay(50);  
 }

 foreArm.write(10);   // 0 - 100, 10
 wristFlex.write(40); // 0 - 150, 40
 wristRotate.write(0);  // 0 - 180, 0

 for(int i = 90; i < 150; i += 1)
 { 
   claw.write(i);       // 90 - 140,    
   delay(50);
 }
 for(int j = 150; j > 90; j -= 1)
 {
   claw.write(j);       // 90 - 140,    
   delay(50);
 }
}
void control()
{
 if(Serial.available())
 {
  for(int i = 0; i < no_of_fields; i++)
  {
   inCommand[i] = Serial.parseFloat();
  }

  unsigned long time1 = millis();

  while (Serial.read() != -1)
  {
   //loops here until serial buffer becomes empty
   //Serial.println(millis() - time1);
   digitalWrite(ledPin, HIGH);
  }

  digitalWrite(ledPin,LOW); 

  //echo the incoming command sequence
  EchoData(inCommand);

  //now do something with the inCommand[] array.... 
  base.write(inCommand[0]);
  shoulder.write(inCommand[1]);
  foreArm.write(inCommand[2]);
  wristFlex.write(180 - inCommand[3]);
  wristRotate.write(inCommand[4]);
  claw.write(inCommand[5]);

  //clear the inCommand[] array
  ClearOldData(inCommand);
 }
}

void loop()
{  
  demo();
}
