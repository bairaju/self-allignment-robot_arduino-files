#include "servos.h"
Servo servo0; 
Servo servo1; 
Servo servo2; 

void setup() {
  servo0.attach(3);  // attaches the servo on pin 3 to the servo object
  servo1.attach(4);  // attaches the servo on pin 4 to the servo object
  servo2.attach(5);  // attaches the servo on pin 5 to the servo object
}

void loop() {
  static int totalLoops = 5 * UPDATES_PER_SECOND; // run for 5 seconds
  while(totalLoops)               // main loop, exit and turn off after totalLoops
  {
    servoLoop0();
    servoLoop1();
    servoLoop2();
    delay(1000 / UPDATES_PER_SECOND);     // update the servos this often     
    totalLoops = totalLoops - 1;    
  }
  homeServos(); 
}

void homeServos(void){
  static int totalLoops = 2 * UPDATES_PER_SECOND; // allow homing to last 2 seconds
  while(totalLoops)               // homing loop, exit and turn off after totalLoops
  {  
    servoHome0();
    servoHome1();
    servoHome2();
    delay(1000 / UPDATES_PER_SECOND);     // update the servos this often     
    totalLoops = totalLoops - 1;        
  }
  servo0.detach();
  servo1.detach();
  servo2.detach();    
  while(1){
    /*spin here forever*/}  
}

