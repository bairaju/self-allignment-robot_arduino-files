 #include <Servo.h>
 //Servo myservo; 
 Servo five_servo;
 //int myservo_position = 0; 
 int servo_position = 0;

void setup() {
  // put your setup code here, to run once:

  five_servo.attach (6);

  //five_servo.write(60);
}

void loop() {
  // put your main code here, to run repeatedly:

  five_servo.write(160);
  delay(2000);
  five_servo.write(10);
  delay(2000);

  five_servo.write(10);
  delay(2000);
  five_servo.write(10);
  delay(2000);

}
