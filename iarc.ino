#include<math.h>

#define s1 2 
#define s2 4
#define s3 16
#define s4 17
#define s5 5
#define s6 18
#define s7 19
#define ma1  27//Right motor
#define ma2  26 
#define mb1  12//Left motor
#define mb2  14
#define en1  25
#define en2  13
#define block 15



float  Kp = 0.06;
float Ki = 0.0008;
float  Kd = 0.1;
             
int P;
int I;
int D;

int lastError;


void setup() {
  // put your setup code here, to run once:
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s5,INPUT);
  pinMode(s6,INPUT);
  pinMode(s7,INPUT);
  pinMode(ma1,OUTPUT);
  pinMode(ma2,OUTPUT);
  pinMode(mb1,OUTPUT);
  pinMode(mb2,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(block,INPUT);
  Serial.begin(115200);
  }

void loop() {
  pid();
}


int readline()
{ bool a1,a2,a3,a4,a5,a6,a7;
  int position;
  a1 = not(digitalRead(s1));
  a2 = not(digitalRead(s2));
  a3 = not(digitalRead(s3));
  a4 = not(digitalRead(s4));
  a5 = not(digitalRead(s5));
  a6 = not(digitalRead(s6));
  a7 = not(digitalRead(s7));
  
  
//  Serial.print(a1);
//  Serial.print(a2);
//  Serial.print(a3);
//  Serial.print(a4);
//  Serial.print(a5);
//  Serial.print(a6);
//  Serial.println(a7);
  if((a1+a2+a3+a4+a5+a6+a7)!=0){
  position = ((a1*0)+(a2*3000)+(a3*5000)+(a4*6000)+(a5*7000)+(a6*9000)+(a7*25000))/(a1+a2+a3+a4+a5+a6+a7);}
  else{
    stfu();
    }
//  Serial.print("position = ");
//  Serial.println(position);
  return position;}

int pid()
{
  uint16_t positionLine = readline();
  int error = 6000-positionLine;

  P = error;
  I = error + I;
  D  = error - lastError;
  lastError = error; 

  int motorSpeedChange = P*Kp  + I*Ki + D*Kd;

  int motorSpeedA = 125 + motorSpeedChange;
  int motorSpeedB  = 125 - motorSpeedChange;
 
  if (motorSpeedA > 250) {
    motorSpeedA =  250;
  }
  if (motorSpeedB > 250) {
    motorSpeedB = 250;
  }
  if  (motorSpeedA < -250) {
    motorSpeedA = -250;
  }
  if (motorSpeedB < -250)  {
    motorSpeedB = -250;
  }

//  Serial.print("error = ");
//  Serial.println(error);
//  Serial.print(motorSpeedB);
//  Serial.print(" ");
//  Serial.println(motorSpeedA);
  go(motorSpeedA,motorSpeedB);
  return error;
}

void go(int spl,int spr){

  if(spr>=0){
    digitalWrite(ma1,HIGH);
    digitalWrite(ma2,LOW);
    }
  else{
    digitalWrite(ma1,LOW);
    digitalWrite(ma2,HIGH);
   }
  if(spl>=0){
    digitalWrite(mb1,HIGH);
    digitalWrite(mb2,LOW);
    }
  else{
    digitalWrite(mb1,LOW);
    digitalWrite(mb2,HIGH);
   }
  spr = abs(spr);
  spl = abs(spl);
  analogWrite(en1,spr);
  analogWrite(en2,spl);
  Serial.print(spl);
  Serial.println(spr);
  }

void stfu(){//stop function
  analogWrite(en1,0);
  analogWrite(en2,0);
  digitalWrite(ma1,LOW);
  digitalWrite(ma2,LOW);
  digitalWrite(mb1,LOW);
  digitalWrite(mb2,LOW);
}
