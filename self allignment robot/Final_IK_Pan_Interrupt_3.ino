//**************************************************************************************************
//Calcs for a circle...
//http://sites.csn.edu/istewart/Math126/circles/circles.htm
//_________________________________________________________________________________
//Quadratic Equation...
//http://home.windstream.net/okrebs/page6.html
//__________________________________________________________________________________
//ok site for arduino 3dof IK...
//http://te.unib.ac.id/lecturer/indraagustian/2014/05/3dof-inverse-kinematic-for-armleg-of-robot-use-arduino/
//_____________________________________________________________________________________
//Arduino Code...
//https://www.circuitsathome.com/mcu/robotic-arm-inverse-kinematics-on-arduino/
//_____________________________________________________________________________________
//Explination of IK...
//http://www.learnaboutrobots.com/inverseKinematics.htm
//_____________________________________________________________________________________
//Arduino and Servocity parts...
//http://www.instructables.com/id/Homemade-Robotic-Arm-Using-Standard-Parts-Using-Ar/
//_____________________________________________________________________________________
//IK sketch info...
//http://www.gperco.com/2013/12/robot-arm-reaching-for-stars.html
//_____________________________________________________________________________________
//Solving Triangle Trig functions...
//https://brownmath.com/twt/solving.htm
//https://brownmath.com/twt/solving.htm#SSA
//https://brownmath.com/twt/refangle.htm
//_____________________________________________________________________________________
//Solve for second point using a circle...
//https://math.stackexchange.com/questions/1702990/determine-the-third-point-in-right-triangle-only-knowing-the-coordinates-of-the
//_____________________________________________________________________________________
//Algebra Calculator...
//https://www.mathpapa.com/algcalc/?utm_expid=69051716-45.fVyjbY6-TPO7Vpx8ux9t8A.1&utm_referrer=https%3A%2F%2Fwww.mathpapa.com%2F
//______________________________________________________________________________________
//Circle Line Intersection...
//http://mathworld.wolfram.com/Circle-LineIntersection.html
//_______________________________________________________________________________________
//Find the Points of Intersection of a Circle with a Line
//http://www.analyzemath.com/CircleEq/circle_line_intersection.html
//_____________________________________________________________________________________
//Determine third point of triangle when two points and all sides are known?
//https://math.stackexchange.com/questions/543961/determine-third-point-of-triangle-when-two-points-and-all-sides-are-known
//___________________________________________________________________________________
//How to solve a triangle formed by three (x,y) points.
//http://www.teacherschoice.com.au/Maths_Library/Trigonometry/triangle_given_3_points.htm
//____________________________________________________________________________________
//Solution of triangles
//https://en.wikipedia.org/wiki/Solution_of_triangles
//____________________________________________________________________________________
//Very good website...
//Law of Cosines
//https://www.mathsisfun.com/algebra/trig-cosine-law.html
//The Law of Sines
//http://www.mathsisfun.com/algebra/trig-sine-law.html
//Solving Triangles
//http://www.mathsisfun.com/algebra/trig-solving-triangles.html
//Solving SSS Triangles
//http://www.mathsisfun.com/algebra/trig-solving-sss-triangles.html
//_____________________________________________________________________________________
//30-60-90 Triangle: Theorem, Properties & Formula
//http://study.com/academy/lesson/30-60-90-triangle-theorem-properties-formula.html
//_____________________________________________________________________________________
// Notes:
//  - Use 8.5 volts and 5 amps for servos but not gearbox servo. Must use seperate power supply for
//    gearbox.
//
//***************************************************************************************************


#pragma once;
#include <SPI.h>
#include <Pixy.h>
#include <Servo.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <math.h>



Pixy pixy;


Servo BasePan, GripTilt, ShoulderTilt, ElbowTilt, WristTilt; // create servo object to control a servo.
//Servo counting goes from 0 to 4.
//Grip = 0  Wrist = 1  Elbow = 2   Shoulder = 3  Base = 4

MPU6050 accelgyro;

#define X_CENTER        ((PIXY_MAX_X - PIXY_MIN_X)/2)
#define Y_CENTER        ((PIXY_MAX_Y - PIXY_MIN_Y)/2)

boolean Pan_On = true;      //turn on PanTilt function.
boolean FoundBlock = false;
uint16_t blocks, j;
int pos, CurrentAngle;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int i, k;
bool Centered;
int LoopCounter = 1;
int PanTarget = X_CENTER;

//****** Setup IK Variables ******
#define PI 3.14159265

float ShoulderLength = 6.0;
float ElbowLength = 4.0;
float WristLength = 4.0;
float Hypoth, Slope, CirclePointX, CirclePointY;
float x1 = 6.0;//Target end point.10.6
float y1 = 5.0;//Target end point.7.5
float x2 = 0.0;//origin start point.
float y2 = 0.0;//origin start point.
float A, B, C,
      PosXAnswer,   //positive X portion of Quadratic Equation.
      PosYAnswer,   //positive Y portion of Qudratic Equation.
      NegXAnswer,   //negative X portion of Quadratic Equation.
      NegYAnswer,   //negative Y portion of Quadratic Equation.
      Angle_A,      //Angle located at origin (0,0).
      Angle_A_Temp, //Second 1/2 of Angle located at origin (0,0).Shoulder servo setting.
      Angle_B,      //Elbow servo setting.
      Angle_C;      //Wrist servo setting subtracted from 180.

//********************************

//****** Setup Interrupt Variables **********************************
//Board	        int.0	int.1	int.2	int.3	int.4	int.5
//Uno, Ethernet	2	3
//Mega2560	2	3	21	20	19	18

const byte InterruptPin = 18;
int InterruptNumber = 5;
volatile boolean InterruptOccured = false;


//**********************************************************************


void setup()
{
  Wire.begin();
  Serial.begin(9600);

  //**************** Initialize I2C devices **************
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection. Clever code for testing a true/false condition.
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  //**************** Initialize interrupts **************
  pinMode(InterruptPin, INPUT_PULLUP);//Must use PULLUP with LOW.

  pinMode( 9, OUTPUT); //Base pin.
  pinMode( 10, OUTPUT); //Shoulder pin.
  pinMode( 11, OUTPUT); //Elbow pin.
  pinMode( 8, OUTPUT); //Wrist pin.
  pinMode( 7, OUTPUT); //Grip
  pinMode(13, OUTPUT);//Indicates when electromagnet is energized.
  pinMode(12, OUTPUT); //Used to switch electromagnet on/off.


  BasePan.attach(9);  // attaches the servo on pin 9 to the servo object
  GripTilt.attach(7);  // attaches the servo on pin 7 to the servo object
  ShoulderTilt.attach(10);  // attaches the servo on pin 10 to the servo object
  ElbowTilt.attach(11);  // attaches the servo on pin 11 to the servo object. Can not use Pin 11.
  WristTilt.attach(8);// attaches the servo on pin 8 to the servo object

  Centered = false;

  //**************** Initialize servos **************
  Serial.println("Initializing Servos...");
  ResetServos();


  // ************* Initialize Pixy Camera ************
  pixy.init();



}//end setup.




void loop()
{

  Serial.println("Running...");



  for (i = 1; i < 4; i = i + 1) {
    blocks = pixy.getBlocks(); //blocks = number  pixy.blocks[0].x pixy.blocks[0].x pixy.blocks[0].xof blocks in Pixymon. If true; this starts the locating an object process.
    delay(50); //required.Slow down the process for serial communication from Pixy.
  }

  if (blocks) //If there is an object in the Pixymon viewer.
  {
    FoundBlock = true; //set found a block flag to true.

    while (Pan_On)
    {
      Pan();
    } //end while pan_on.


    if ((pixy.blocks[0].y >= 5) && (pixy.blocks[0].y < 25)) { //position 12.
      x1 = 11;
      y1 =1;
    }//end if.

    if ((pixy.blocks[0].y >= 25) && (pixy.blocks[0].y < 47)) { //position 11.
      x1 = 10;
      y1 = 3;
    }//end if.

    if ((pixy.blocks[0].y >= 47) && (pixy.blocks[0].y < 72)) { //position 10.
      x1 = 8 ;
      y1 = 3;//was 4.
    }//end if.

    if ((pixy.blocks[0].y >= 72) && (pixy.blocks[0].y < 87)) { //position 9.
      x1 = 8;
      y1 = 1;
    }//end if.

    if ((pixy.blocks[0].y >= 87) && (pixy.blocks[0].y < 115)) { //position 8.
      x1 = 7 ;
      y1 = 2;
    }//end if.


/******************* TO BE CALCULATED OUT ***************************************
    if ((pixy.blocks[0].y > 154) && (pixy.blocks[0].y < 173)) { //position 7.
      x1 = 3 ;
      y1 = 8;
    }//end if.

    if ((pixy.blocks[0].y > 174) && (pixy.blocks[0].y < 193)) { //position 6.
      x1 = 3 ;
      y1 = 7;
    }//end if.
************************************************************************************/

    if ((x1 < ShoulderLength) && (y1 < ShoulderLength)) {
      Special_Calc_Point();
      delay(1000);
    }//end if x1 & y1 < ShoulderLength.
    else {
      Calc_Point();
      delay(1000);

    }//end else.

  }//end if blocks.


  if (FoundBlock)
  {
    FoundBlock = false; //reset found a block flag.
    

    Pan(); //Now closer, check pan again.
    PickUp();
  }//end if FoundBlock.


  ResetServos();
  delay(5000);     //pause.
  Pan_On = true;   //turn on PanTilt function.



}//end Loop.



//**********************************************************************************
//              Level
//**********************************************************************************
void Level()
{
  Serial.println("in Level...");
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  pos = constrain(map(ax, -15000, 15000, 0, 180), 0, 180); //ay is the pitch (front to back);


  while (pos != 90)
  {


    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    pos = constrain(map(ax, -15000, 15000, 0, 180), 0, 180); //ay is the pitch (front to back);

    if (pos > 90) {
      GripTilt.write(GripTilt.read() - 1); //Raise the Grip.
      delay(50);
    } //end if pos < 90.

    if (pos < 90) {
      GripTilt.write(GripTilt.read() + 1);
      delay(50);
    }

    if (pos == 90) {

      break;
    }

  } //end while.

}//end Level.



//**************************************************************************************
//                            Special_Calc_Point
//**************************************************************************************
void Special_Calc_Point() {

  Hypoth = sqrt(sq(x1) + sq(y1)) + WristLength;
  A = ElbowLength;//4;
  B = Hypoth;//B_Value;//6.7; //check here for nan.
  C = ShoulderLength;//6;


  //*** Calculate angle A ***//
  Angle_A = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);
  //    Angle_A_Temp = acos((sq(x1) + sq(Hypoth) - sq(y1)) / (2 * x1 * Hypoth))*(180 / PI); //Second 1/2 of Angle A from X axis upto Shoulder arm.
  //    Angle_A = Angle_A + Angle_A_Temp; //Second 1/2 of Angle A from X axis plus Shoulder arm angle.
  // Angle_A = map(Angle_A, 0, 90, 30, 70); //must map values since using a gearbox and limits at 30 and 65.Largest shoulder degree:109.


  //*** Calculate angle B ***//
  Angle_B =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);

  //*** Calculate angle C ***//
  Angle_C = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B)) * (180 / PI);
  //  Angle_C = 180 - Angle_C; //must calc larger opposite side angle.

  Angle_A = Angle_A * (1 + (Angle_A / (Angle_B + Angle_C)));

  if (Angle_A < 35) {
    Angle_A = 35;
  }//End if <35.



  if (!isnan(Angle_A)) {
    Serial.println(Angle_A);
    ShoulderTilt.write(Angle_A);
    delay(1000);
  }


  if (!isnan(Angle_B)) {

    CurrentAngle = ElbowTilt.read();

    if (Angle_B > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i < Angle_B; i = i + 1) //if Angle_B > CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(10);
      }//end for CurrentAngle.

    }//end if Angle_B > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i > Angle_B; i = i - 1) //if Angle_B < CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(10);
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.



  if (!isnan(Angle_C)) {

    CurrentAngle = WristTilt.read();

    if (Angle_C > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i < Angle_C; i = i + 1) //if Angle_C > CurrentAngle.
      {

        WristTilt.write(i);
        delay(10);
      }//end for CurrentAngle.

    }//end if Angle_C > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i > Angle_C; i = i - 1) //if Angle_C < CurrentAngle.
      {

        WristTilt.write(i);
        delay(10);
      }//end for CurrentAngle.
    }//end else.

  } //end if isnan.

}//end Special_Calc_Point.



//******************************************************************************
//                  Calc_Point
//******************************************************************************
void Calc_Point() {
  //*********** Line Calcs *************************************
  Slope = (y2 - y1) / (x2 - x1);
  Serial.print("Slope: ");
  Serial.println(Slope, 4);


  //*********** Target Circle Calcs *****************************
  A = 1 + sq(y1 / x1);
  B = (-2 * x1) + (-2 * y1 * Slope);
  C = sq(y1) + sq(x1) - sq(WristLength);



  //***************************************************************
  //************ Quadratic Equation *******************************
  //***************************************************************

  /*
  Use: sqrt (-1);  // Set to not a number...nan.
  */

  Serial.println();

  //************************//
  //*** Negative Portion ***//
  //************************//

  NegXAnswer = ((-1 * B) - (sqrt(sq(B) - (4 * A * C)))) / (2 * A); //Minus portion of Quadratic Equation.
  NegYAnswer = Slope * NegXAnswer;

  if (!isnan(NegXAnswer)) {

    Serial.print("Negative Point: ");
    Serial.print(NegXAnswer);
    Serial.print(",");
    Serial.println(NegYAnswer);
    Serial.println();

    Calc_Circle(NegXAnswer, NegYAnswer);
  }//end if Negative !isnan.

  else
  {


    //************************
    //*** Positive Portion ***
    //************************

    PosXAnswer = ((-1 * B) + (sqrt(sq(B) - (4 * A * C)))) / (2 * A); //Plus portion of Quadratic Equation.
    PosYAnswer = Slope * PosXAnswer;

    if (!isnan(PosXAnswer)) {
      Serial.print("**** Positive Point: ");
      Serial.print(PosXAnswer);
      Serial.print(",");
      Serial.println(PosYAnswer);
      Serial.println();

      Calc_Circle(PosXAnswer, PosYAnswer);

    }//end if Positive !isnan.

  }//end else.

}//end Calc_Point.

//**********************************************************************************
//                  Calc_Circle
//**********************************************************************************

void Calc_Circle(float BXValue, float BYValue) {
  //******************************************************************
  //*********** Starting Circle Calcs ********************************
  //******************************************************************

  Hypoth = sqrt(sq(BXValue) + sq(BYValue));
  A = ElbowLength;//4;
  B = Hypoth;//B_Value;//6.7; //check here for nan.
  C = ShoulderLength;//6;





  Angle_A_Temp = acos((sq(x1) + sq(Hypoth) - sq(y1)) / (2 * x1 * Hypoth)) * (180 / PI); //Second 1/2 of Angle A from X axis upto Shoulder arm.
  //  Angle_A = Angle_A + Angle_A_Temp; //Second 1/2 of Angle A from X axis plus Shoulder arm angle.
  // Angle_A = map(Angle_A, 0, 115, 30, 70); //must map values since using a gearbox and limits at 30 and 65.Largest shoulder degree:109.

  //*** Calculate angle B ***//
  Angle_B =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);


  //*** Calculate angle C ***//
  Angle_C = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B)) * (180 / PI);
  Angle_C = 180 - Angle_C; //must calc larger opposite side angle.


  //*** Calculate angle A ***//
  Angle_A = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);

  Angle_A = Angle_A * (1 + (Angle_A / (Angle_B + Angle_C)));

  if (Angle_A < 35) {
    Angle_A = 35;
  }//End if <35.


  if (!isnan(Angle_A)) {
    Serial.println(Angle_A);
    ShoulderTilt.write(Angle_A);
    delay(1000);
  }

  if (!isnan(Angle_B)) {

    CurrentAngle = ElbowTilt.read();

    if (Angle_B > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i < Angle_B; i = i + 1) //if Angle_B > CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(10);
      }//end for CurrentAngle.

    }//end if Angle_B > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i > Angle_B; i = i - 1) //if Angle_B < CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(10);
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.



  if (!isnan(Angle_C)) {

    CurrentAngle = WristTilt.read();

    if (Angle_C > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i < Angle_C; i = i + 1) //if Angle_C > CurrentAngle.
      {

        WristTilt.write(i);
        delay(10);
      }//end for CurrentAngle.

    }//end if Angle_C > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i > Angle_C; i = i - 1) //if Angle_C < CurrentAngle.
      {

        WristTilt.write(i);
        delay(10);
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.

}//end Calc_Circle.


//********************************************
//              Pan
// Note: There can be a block/object centered in the Pixymon viewer. But it could be close or far away. Must zoom in/out for distance.
// The PanTilt routine just gets the block/object centered in the screen NOT the distance. This distance X_CENTER = 159 and Y_CENTER = 99.
//********************************************
void Pan()
{

Serial.println("Now in Pan...");

  while (Pan_On) //Now Pan...
  {

    blocks = pixy.getBlocks(); //Check for objects.
    delay(40);

    PanTarget = pixy.blocks[0].x; //set distance from object.

    Serial.print("PanTarget (198-200).... ");
    Serial.println(PanTarget);

 //   if (inRange(PanTarget, 160, 180))
      if (inRange(PanTarget, 198, 200))
    { 
      delay(1500);
      Serial.println("**** Found ****");
      Pan_On = false;
    }//end PanTarget 160-180 if.

    if (PanTarget > 200) //Was 180.
    {
      BasePan.write(BasePan.read() - 1);
      delay(500); //wait 2 seconds for servo to completely stop. was 50.
    }//end PanTarget>180 if.


    if (PanTarget < 198) //was 160
    {
      BasePan.write(BasePan.read() + 1);
      delay(500); //wait 2 seconds for servo to completely stop. was 50.
    }//end PanTarget<160 if.


  }//end while


}//end Pan.



//*************************************************************
//                  ResetServos
//*************************************************************
void ResetServos()
{


  ShoulderTilt.write(65);//was 50.60.35.55
  delay(2000);


  if (ElbowTilt.read() < 80) {
    for (i = ElbowTilt.read(); i < 81; i = i + 2) {
      ElbowTilt.write(i );
      delay(200);
    }//end for
  }//end if
  else
  {
    for (i = ElbowTilt.read(); i >= 80; i = i - 2) {
      ElbowTilt.write(i );
      delay(200);
    }//end for
  }//end else


  if (WristTilt.read() < 50) {
    for (i = WristTilt.read(); i < 51; i = i + 2) {
      WristTilt.write(i );
      delay(200);
    }//end for
  }//end if
  else
  {
    for (i = WristTilt.read(); i >= 50; i = i - 2) {
      WristTilt.write(i );
      delay(200);
    }//end for
  }//end else


  if (GripTilt.read() < 10) {
    for (i = GripTilt.read(); i < 11; i = i + 2) {
      GripTilt.write(i);
      delay(200);
    }//end for
  }//end if
  else
  {
    for (i = GripTilt.read(); i >= 10; i = i - 2) {
      GripTilt.write(i );
      delay(200);
    }//end for
  }//end else


} //End ResetServos.

//*****************************************************************************
//                  PrintInfo
//*****************************************************************************
void PrintInfo()
{


  blocks = pixy.getBlocks(); //blocks = number  pixy.blocks[0].x pixy.blocks[0].x pixy.blocks[0].xof blocks in Pixymon. If true; this starts the locating an object process.
  delay(40); //required.Slow down the process for serial communication from Pixy

  Serial.print("X_CENTER ");
  Serial.print(X_CENTER);
  Serial.println("");
  Serial.print("Y_CENTER ");
  Serial.print(Y_CENTER);
  Serial.println("");
  Serial.print("pixy.blocks[0].y ");
  Serial.print(pixy.blocks[0].y);
  Serial.println("");
  Serial.print("pixy.blocks[0].x ");
  Serial.print(pixy.blocks[0].x);
  Serial.println("");
  delay(2000);

}//end PrintInfo.



//***************************************************
//      inRange
// Do  include minimum and maximum values
//***************************************************
bool inRange(int val, int minimum, int maximum)
{

  return ((minimum <= val) && (val <= maximum));

}//end inRange


//******************************************************************************
//      PickUp
//******************************************************************************
void PickUp()
{
  int TempHold = ShoulderTilt.read();//store the current degrees.
  
  ShoulderTilt.write(50);//move magnet out of the way.
  delay(4000);
  
  i = 0; //initialize counter.
  MagnetOn();
  Level();
 
  ShoulderTilt.write(TempHold);//return to position AFTER Level.
   delay(4000);
  Level(); //re-Level since may be touching table top.

  InterruptOccured = false;

  while (true)
  {

    attachInterrupt(InterruptNumber, isr, CHANGE);//Start checking for interrupts.Was RISING.LOW
    //>>>> After isr routine returns HERE! <<<<
    if(InterruptOccured){break;}
    
    i = i + 1;
    Serial.print("Looking...>> ");
    Serial.println(i);
    ShoulderTilt.write(TempHold - i);
    delay(1000);
    detachInterrupt(InterruptNumber);//Stop checking and turn off checking for interrupts.

  }//end while.

  ShoulderTilt.write(50);
  delay(4000);
  MagnetOff();
  
}//end loop

//**********************************************************
//              ISR
//**********************************************************
void isr()
{

  InterruptOccured = true;
  Serial.println(">> Just touched <<");
  Serial.println(InterruptOccured);

}//end isr



//******************************************************************************
//      MagnetOn
//******************************************************************************
void MagnetOn()
{
  Serial.println("Magnet On...>>");
  digitalWrite(13, HIGH); // Turn on the light to indicate magnet is activated.
  digitalWrite(12, HIGH); // Turn on the magnet.
  delay(250);//debug.
  
}//end MagnetOn.

//******************************************************************************
//      MagnetOff
//******************************************************************************
void MagnetOff()
{
  Serial.println("Magnet Off...<<");
  digitalWrite(13, LOW); // Turn off the light to indicate magnet is deactivated.
  digitalWrite(12, LOW); // Turn off the magnet.
  delay(250);//debug.
}//end MagnetOn.

