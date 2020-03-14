#include<Servo.h>
#include<SoftwareSerial.h>
Servo base,shoulder,elbow,wrist;
int pos1,pos2,pos3,pos4;



void setup() {
  // put your setup code here, to run once:
base.attach(9);
shoulder.attach(10);
elbow.attach(11);
wrist.attach)12);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
base.write(90);
shoulder.write(0);
elbow.write(45);
wrist.write(45);
delay(1000);
if (Serial.available())
{
char c;
c=Serail.read();
Serial.print(c);
if (c='p')
{
base.write(90);
elbow.write(45);
wrist.write(45);
delay(1000);
for(pos2=0;pos2<=45;pos2+=1);
shoulder.write(pos2);
delay(15);
}
delay(1000);
base.write(90);
elbow.write(45);
wrist.write(45);
delay(1000)
for(pos2=45;pos>=0;pos2-=1)
{
  shoulder.write(pos2);
  delay(15);
}
delay(1000);
}




}
        
        }
    }

}
}
