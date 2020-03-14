// connect motor controller pins to Arduino digital pins
// motor one
int in1 = 2;
int in2 = 3;
// motor two
int in3 = 5;
int in4 = 6;
// motor three
int in5 = 8;
int in6 = 9;
// motor two
int in7 = 11;
int in8 = 12;
void setup()
{
  // set all the motor control pins to outputs
  

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // turn on motor C
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  // turn on motor D
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH); 
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW); 
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
  delay(500);
}
  void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5,LOW);
  digitalWrite(in6,HIGH);
  digitalWrite(in7,LOW);
  digitalWrite(in8,HIGH);
  delay(2000);
 digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW); 
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW); 
  
  void loop()
{
  demoOne();
  delay(1000);
  demoTwo();
  delay(1000);
}
