int motor1_forward=6;
int motor1_reverse=2;
int motor2_forward=5;
int motor2_reverse=4;
int motor3_forward=7;
int motor3_reverse=13;
int motor4_forward=12;
int motor4_reverse=8;
int pot1=A1;
int pot2=A2;
int en1_motor1=10;
int en2_motor1=11;
int en1_motor2=9;
int en2_motor2=3;

int val1;
int val2;
int a,b,c,d,e,f,g,h;


//the setup routine runs once when you press reset

void setup()
{
// initialize the digital pin as an output

pinMode(motor1_forward, OUTPUT);
pinMode(motor1_reverse, OUTPUT);
pinMode(motor2_forward, OUTPUT);
pinMode(motor2_reverse, OUTPUT);
pinMode(motor3_forward, OUTPUT);
pinMode(motor3_reverse, OUTPUT);
pinMode(motor4_forward, OUTPUT);
pinMode(motor4_reverse, OUTPUT);
Serial.begin(9600);
}


void forward()
{
digitalWrite(motor1_forward,0); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,1); //terminal D2 will be LOW

digitalWrite(motor2_forward,0); //terminal D1 will be LOW
digitalWrite(motor2_reverse,1); //terminal D2 will be HIGH

digitalWrite(motor3_forward,0); //terminal D1 will be LOW
digitalWrite(motor3_reverse,1); //terminal D2 will be LOW

digitalWrite(motor4_forward,0); //terminal D1 will be LOW
digitalWrite(motor4_reverse,1); //terminal D2 will be LOW
}


void reverse()
{
digitalWrite(motor1_forward,1); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,0); //terminal D2 will be LOW

digitalWrite(motor2_forward,1); //terminal D1 will be LOW
digitalWrite(motor2_reverse,0); //terminal D2 will be HIGH

digitalWrite(motor3_forward,1); //terminal D1 will be LOW
digitalWrite(motor3_reverse,0); //terminal D2 will be LOW

digitalWrite(motor4_forward,1); //terminal D1 will be LOW
digitalWrite(motor4_reverse,0); //terminal D2 will be LOW
}


void right()
{
digitalWrite(motor1_forward,0); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,1); //terminal D2 will be LOW

digitalWrite(motor2_forward,0); //terminal D1 will be LOW
digitalWrite(motor2_reverse,1); //terminal D2 will be HIGH

digitalWrite(motor3_forward,1); //terminal D1 will be LOW
digitalWrite(motor3_reverse,1); //terminal D2 will be LOW

digitalWrite(motor4_forward,1); //terminal D1 will be LOW
digitalWrite(motor4_reverse,1); //terminal D2 will be LOW
}

void left()
{
digitalWrite(motor1_forward,1); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,1); //terminal D2 will be LOW

digitalWrite(motor2_forward,1); //terminal D1 will be LOW
digitalWrite(motor2_reverse,1); //terminal D2 will be HIGH

digitalWrite(motor3_forward,0); //terminal D1 will be LOW
digitalWrite(motor3_reverse,1); //terminal D2 will be LOW

digitalWrite(motor4_forward,0); //terminal D1 will be LOW
digitalWrite(motor4_reverse,1); //terminal D2 will be LOW
}


void clockwise()
{
digitalWrite(motor1_forward,0); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,1); //terminal D2 will be LOW

digitalWrite(motor2_forward,0); //terminal D1 will be LOW
digitalWrite(motor2_reverse,1); //terminal D2 will be HIGH

digitalWrite(motor3_forward,1); //terminal D1 will be LOW
digitalWrite(motor3_reverse,0); //terminal D2 will be LOW

digitalWrite(motor4_forward,1); //terminal D1 will be LOW
digitalWrite(motor4_reverse,0); //terminal D2 will be LOW
}

void anticlockwise()
{
digitalWrite(motor1_forward,1); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,0); //terminal D2 will be LOW

digitalWrite(motor2_forward,1); //terminal D1 will be LOW
digitalWrite(motor2_reverse,0); //terminal D2 will be HIGH

digitalWrite(motor3_forward,0); //terminal D1 will be LOW
digitalWrite(motor3_reverse,1); //terminal D2 will be LOW

digitalWrite(motor4_forward,0); //terminal D1 will be LOW
digitalWrite(motor4_reverse,1); //terminal D2 will be LOW
}

void reverse_right()
{
digitalWrite(motor1_forward,1); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,0); //terminal D2 will be LOW

digitalWrite(motor2_forward,1); //terminal D1 will be LOW
digitalWrite(motor2_reverse,0); //terminal D2 will be HIGH

digitalWrite(motor3_forward,1); //terminal D1 will be LOW
digitalWrite(motor3_reverse,1); //terminal D2 will be LOW

digitalWrite(motor4_forward,1); //terminal D1 will be LOW
digitalWrite(motor4_reverse,1); //terminal D2 will be LOW
}

void reverse_left()
{
digitalWrite(motor1_forward,1); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,1); //terminal D2 will be LOW

digitalWrite(motor2_forward,1); //terminal D1 will be LOW
digitalWrite(motor2_reverse,1); //terminal D2 will be HIGH

digitalWrite(motor3_forward,1); //terminal D1 will be LOW
digitalWrite(motor3_reverse,0); //terminal D2 will be LOW

digitalWrite(motor4_forward,1); //terminal D1 will be LOW
digitalWrite(motor4_reverse,0); //terminal D2 will be LOW
}



// the loop routine runs over and over again forever
void loop()
{

val1=analogRead(pot1);
val2=analogRead(pot2);


if(val1>=510&&val1<=540&&val2>=510&&val2<=540)				//no input
{
digitalWrite(motor1_forward,1); //terminal D1 will be HIGH
digitalWrite(motor1_reverse,1); //terminal D2 will be LOW

digitalWrite(motor2_forward,1); //terminal D1 will be LOW
digitalWrite(motor2_reverse,1); //terminal D2 will be HIGH

digitalWrite(motor3_forward,1); //terminal D1 will be LOW
digitalWrite(motor3_reverse,1); //terminal D2 will be LOW

digitalWrite(motor4_forward,1); //terminal D1 will be LOW
digitalWrite(motor4_reverse,1); //terminal D2 will be LOW
}

else if(val1>540&&val2>540)			//forward
{
a = map(val1,540,1023,0,255);
analogWrite(en1_motor1,a);
analogWrite(en2_motor1,a);
analogWrite(en1_motor2,a);
analogWrite(en2_motor2,a);
forward();
}

else if(val1<510&&val2<510)			//reverse
{
b=map(val1,0,510,0,255);
analogWrite(en1_motor1,b);
analogWrite(en2_motor1,b);
analogWrite(en1_motor2,b);
analogWrite(en2_motor2,b);
reverse();
}

else if(val1>540&&val2>=510&&val2<=540)			//right
{
c=map(val1,540,1023,0,255);
analogWrite(en1_motor1,c);
analogWrite(en2_motor1,c);
analogWrite(en1_motor2,c);
analogWrite(en2_motor2,c);
right();
}

else if(val1>=510&&val1<=540&&val2>540)		        //left
{
d=map(val2,540,1023,0,255);
analogWrite(en1_motor1,d);
analogWrite(en2_motor1,d);
analogWrite(en1_motor2,d);
analogWrite(en2_motor2,d);
left();
}

else if(val1>540&&val2<510)			//clockwise
{
e=map(val1,540,1023,0,255);
analogWrite(en1_motor1,e);
analogWrite(en2_motor1,e);
analogWrite(en1_motor2,e);
analogWrite(en2_motor2,e);
clockwise();
}

else if(val1<510&&val2>540)			//anticlockwise
{
f = map(val2,540,1023,0,255);
analogWrite(en1_motor1,f);
analogWrite(en2_motor1,f);
analogWrite(en1_motor2,f);
analogWrite(en2_motor2,f);
anticlockwise();
}

else if(val1<510&&val2>=510&&val2<=540)			//reverse right
{
g=map(val1,0,510,0,255);
analogWrite(en1_motor1,g);
analogWrite(en2_motor1,g);
analogWrite(en1_motor2,g);
analogWrite(en2_motor2,g);
reverse_right();
}

else(val1>=510&&val1<=540&&val2<510)
{//reverse left
h=map(val2,0,510,0,255);
analogWrite(en1_motor1,h);
analogWrite(en2_motor1,h);
analogWrite(en1_motor2,h);
analogWrite(en2_motor2,h);
reverse_left();
}


// again the loop will run from begining until the board is turned off
}
