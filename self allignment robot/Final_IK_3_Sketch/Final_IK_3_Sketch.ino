/*
Calcs for a circle...

http://sites.csn.edu/istewart/Math126/circles/circles.htm
_________________________________________________________________________________

Quadratic Equation...

http://home.windstream.net/okrebs/page6.html

__________________________________________________________________________________

ok site for arduino 3dof IK...

http://te.unib.ac.id/lecturer/indraagustian/2014/05/3dof-inverse-kinematic-for-armleg-of-robot-use-arduino/

_____________________________________________________________________________________

Arduino Code...

https://www.circuitsathome.com/mcu/robotic-arm-inverse-kinematics-on-arduino/

_____________________________________________________________________________________

Explination of IK...

http://www.learnaboutrobots.com/inverseKinematics.htm

_____________________________________________________________________________________

Arduino and Servocity parts...

http://www.instructables.com/id/Homemade-Robotic-Arm-Using-Standard-Parts-Using-Ar/

_____________________________________________________________________________________

IK sketch info...

http://www.gperco.com/2013/12/robot-arm-reaching-for-stars.html

_____________________________________________________________________________________

Solving Triangle Trig functions...

https://brownmath.com/twt/solving.htm

https://brownmath.com/twt/solving.htm#SSA

https://brownmath.com/twt/refangle.htm

_____________________________________________________________________________________
Solve for second point using a circle...

https://math.stackexchange.com/questions/1702990/determine-the-third-point-in-right-triangle-only-knowing-the-coordinates-of-the

_____________________________________________________________________________________
Algebra Calculator...
https://www.mathpapa.com/algcalc/?utm_expid=69051716-45.fVyjbY6-TPO7Vpx8ux9t8A.1&utm_referrer=https%3A%2F%2Fwww.mathpapa.com%2F

______________________________________________________________________________________
Circle Line Intersection...

http://mathworld.wolfram.com/Circle-LineIntersection.html

_______________________________________________________________________________________

Find the Points of Intersection of a Circle with a Line

http://www.analyzemath.com/CircleEq/circle_line_intersection.html

_____________________________________________________________________________________
Determine third point of triangle when two points and all sides are known?

https://math.stackexchange.com/questions/543961/determine-third-point-of-triangle-when-two-points-and-all-sides-are-known
___________________________________________________________________________________

How to solve a triangle formed by three (x,y) points.

http://www.teacherschoice.com.au/Maths_Library/Trigonometry/triangle_given_3_points.htm

____________________________________________________________________________________
Solution of triangles
https://en.wikipedia.org/wiki/Solution_of_triangles
____________________________________________________________________________________
Very good website...

Law of Cosines
https://www.mathsisfun.com/algebra/trig-cosine-law.html

The Law of Sines
http://www.mathsisfun.com/algebra/trig-sine-law.html

Solving Triangles
http://www.mathsisfun.com/algebra/trig-solving-triangles.html

Solving SSS Triangles
http://www.mathsisfun.com/algebra/trig-solving-sss-triangles.html
_____________________________________________________________________________________
30-60-90 Triangle: Theorem, Properties & Formula

http://study.com/academy/lesson/30-60-90-triangle-theorem-properties-formula.html

_____________________________________________________________________________________


*/

#include <Servo.h>


Servo BasePan, GripTilt, ShoulderTilt, ElbowTilt, WristTilt; // create servo object to control a servo.
//Servo counting goes from 0 to 4
//Grip = 0  Wrist = 1  Elbow = 2   Shoulder = 3  Base = 4

int pos, CurrentAngle;
int i;


//****** Setup IK variables ******
#define PI 3.14159265

float ShoulderLength = 6.0;
float ElbowLength = 4.0;
float WristLength = 4.0;
float Hypot, Slope, CirclePointX, CirclePointY;
float x1 = 10.0;//Target end point.10.6
float y1 = 7.0;//Target end point.7.5
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


void setup()
{

  Serial.begin(9600);



  pinMode( 9, OUTPUT); //Base pin.
  pinMode( 10, OUTPUT); //Shoulder pin.
  pinMode( 11, OUTPUT); //Elbow pin.
  pinMode( 8, OUTPUT); //Wrist pin.
  pinMode( 7, OUTPUT); //Grip



  BasePan.attach(9);  // attaches the servo on pin 9 to the servo object
  GripTilt.attach(7);  // attaches the servo on pin 7 to the servo object
  ShoulderTilt.attach(10);  // attaches the servo on pin 10 to the servo object
  ElbowTilt.attach(11);  // attaches the servo on pin 11 to the servo object. Can not use Pin 11.
  WristTilt.attach(8);// attaches the servo on pin 8 to the servo object


  // Initialize servos...
  Serial.println("Initializing Servos...");
  ResetServos();

}//end setup.


void loop()
{


  for ( x1 = 3; x1 < 14; x1 = x1 + 1) {

    for (y1 = 1; y1 < 15; y1 = y1 + 1) {


      Serial.println("*******************");
      Serial.println();
      Serial.print("Point: (");
      Serial.print(x1);
      Serial.print(",");
      Serial.print(y1);
      Serial.println(")");
      if ((x1 < ShoulderLength) && (y1 < ShoulderLength)) {
        Special_Calc_Point();

      }//end if x1 & y1 < ShoulderLength.
      else {

        Calc_Point();

      }//end else.
    }//end y1 for.
  }//end x1 for.


}//end Loop.



void Special_Calc_Point() {
  //******************************************************************
  //*********** Starting Special Circle Calcs ********************************
  //******************************************************************

  Hypot = sqrt(sq(x1) + sq(y1)) + WristLength;
  A = ElbowLength;//4;
  B = Hypot;//B_Value;//6.7; //check here for nan.
  C = ShoulderLength;//6;



  //*** Calculate angle A ***//
  Angle_A = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);
  //    Angle_A_Temp = acos((sq(x1) + sq(Hypot) - sq(y1)) / (2 * x1 * Hypot))*(180 / PI); //Second 1/2 of Angle A from X axis upto Shoulder arm.
  //    Angle_A = Angle_A + Angle_A_Temp; //Second 1/2 of Angle A from X axis plus Shoulder arm angle.


  //*** Calculate angle B ***//
  Angle_B =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);

  //*** Calculate angle C ***//
  Angle_C = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B)) * (180 / PI);
  //  Angle_C = 180 - Angle_C; //must calc larger opposite side angle.

  Angle_A = Angle_A * (1 + (Angle_A / (Angle_B + Angle_C))); // Angle A is recalculated due to the servo gearbox used.

  if (Angle_A < 35) {// Angle A is recalculated due to the servo gearbox used.
    Angle_A = 35;
  }//End if <35.



  if (!isnan(Angle_A)) {      //If Angle is a valid number.
    Serial.println(Angle_A);
    ShoulderTilt.write(Angle_A);
    delay(1000);
  }


  if (!isnan(Angle_B)) { //If Angle is a valid number.

    CurrentAngle = ElbowTilt.read();

    if (Angle_B > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i < Angle_B; i = i + 1) //if Angle_B > CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(5);
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
        delay(5);
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.



  if (!isnan(Angle_C)) { //If Angle is a valid number.

    CurrentAngle = WristTilt.read();

    if (Angle_C > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i < Angle_C; i = i + 1) //if Angle_C > CurrentAngle.
      {

        WristTilt.write(i);
        delay(5);
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
        delay(5);
      }//end for CurrentAngle.
    }//end else.

  } //end if isnan.


}//end Special_Calc_Circle.


void Calc_Point() {
  //*********** Line Calcs *********************************
  Slope = (y2 - y1) / (x2 - x1);
  Serial.print("Slope: ");
  Serial.println(Slope, 4);


  //*********** Target Circle Calcs *********************************
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



void Calc_Circle(float BXValue, float BYValue) {
  //******************************************************************
  //*********** Starting Circle Calcs ********************************
  //******************************************************************

  Hypot = sqrt(sq(BXValue) + sq(BYValue));
  A = ElbowLength;//4;
  B = Hypot;//B_Value;//6.7; //check here for nan.
  C = ShoulderLength;//6;


  // Angle_A_Temp = acos((sq(x1) + sq(Hypot) - sq(y1)) / (2 * x1 * Hypot)) * (180 / PI); //Second 1/2 of Angle A from X axis upto Shoulder arm.
  //  Angle_A = Angle_A + Angle_A_Temp; //Second 1/2 of Angle A from X axis plus Shoulder arm angle.

  //*** Calculate angle B ***//
  Angle_B =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);


  //*** Calculate angle C ***//
  Angle_C = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B)) * (180 / PI);
  Angle_C = 180 - Angle_C; //must calc larger opposite side angle.


  //*** Calculate angle A ***//
  Angle_A = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);

  Angle_A = Angle_A * (1 + (Angle_A / (Angle_B + Angle_C))); // Angle A is recalculated due to the servo gearbox used.

  if (Angle_A < 35) {
    Angle_A = 35;
  }//End if <35.


  if (!isnan(Angle_A)) { //If Angle is a valid number.
    Serial.println(Angle_A);
    ShoulderTilt.write(Angle_A);
    delay(1000);
  }

  if (!isnan(Angle_B)) { //If Angle is a valid number.

    CurrentAngle = ElbowTilt.read();

    if (Angle_B > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i < Angle_B; i = i + 1) //if Angle_B > CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(5);
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
        delay(5);
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.



  if (!isnan(Angle_C)) { //If Angle is a valid number.

    CurrentAngle = WristTilt.read();

    if (Angle_C > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i < Angle_C; i = i + 1) //if Angle_C > CurrentAngle.
      {

        WristTilt.write(i);
        delay(5);
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
        delay(5);
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.


}//end Calc_Circle.



//*************************************************************
//                  ResetServos
//*************************************************************
void ResetServos()
{

  ShoulderTilt.write(65);//was 50.60.35.55
  delay(2000);


  ElbowTilt.write(90 );//was 60.70.50.90.40.90
  delay(500);


  WristTilt.write(90);//was 60.50.40
  delay(500);


  GripTilt.write(90); //was 40,35,90,20,60.10.45
  delay(500);


} //End ResetServos.


