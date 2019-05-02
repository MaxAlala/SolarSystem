#include <MatrixMath.h>

#include <Servo.h>


#define N  (4)

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
Servo s6;

double TH1 = 54.81;
double TH2 = 81.45;
double TH3 = 55.71;
double TTH1 = 100; // 0 - 180
double TTH2 = 65; //30 - 100
double TTH3 = 65; // 150 - 0
double TH1_rad = TH1/180*PI;
double TH2_rad = TH2/180*PI;
double TH3_rad = TH3/180*PI;


/// good value -> 5 20 18;
// 5 22 15;
// 0 0 30,25
//    
// INVERSE KINEMATICS

//task
// 22 1 17 - take screwdriver
//21 1 18


// 5 22 15.10 take screwdr  
// 
double a1 = 6;
double a2 = 10;
double a3 = 15.25;
double X0_3 = 1;
double Y0_3 = 1;
double Z0_3 = 30;
double ik_TH1=0;
double ik_TH2=0;
double ik_TH3=0;
double ikTH1_rad = 0;
double ikTH2_rad = 0;
double ikTH3_rad = 0;
double thi1=0;
double thi2=0;
double thi3=0;
double r1 = 0;
double r2=0;
double r3=0;

void getInverseKinematics(){
  r2 = Z0_3 - a1;//15
  r1 = sqrt(X0_3*X0_3 + Y0_3*Y0_3);//10
  r3 = sqrt(r1*r1 + r2*r2);
  thi2 = atan2(r2,r1);
  thi1 = acos((a3*a3 - a2*a2 - r3*r3)/(-2*a2*r3));
  thi3 = acos((r3*r3 - a2*a2 - a3*a3)/(-2*a2*a3));
  ik_TH1 = atan2(Y0_3,X0_3)*180/PI;
  if(ik_TH1> 80 || ik_TH1<-90){
    ik_TH1 = -atan2(Y0_3,-X0_3)*180/PI;

    //
    ik_TH2 = -(90 - thi2*180/PI + thi1*180/PI);
  ik_TH3 = -(180 - thi3*180/PI);
  if(ik_TH2> 90 || ik_TH2<-60 || ik_TH3 < -65 || ik_TH3 > 85){
     ik_TH2 = -(90 - thi2*180/PI - thi1*180/PI);
     ik_TH3 = (180 - thi3*180/PI);
  }
     
  }else{

    ik_TH2 = 90 - thi2*180/PI + thi1*180/PI;
  ik_TH3 = 180 - thi3*180/PI;
  if(ik_TH2> 90 || ik_TH2<-60 || ik_TH3 < -65 || ik_TH3 > 85){
     ik_TH2 = 90 - thi2*180/PI - thi1*180/PI;
     ik_TH3 = -(180 - thi3*180/PI);
  
  }
  }
  

  
  Serial.println("calculatedIK: ");
  Serial.print("ik_TH1: ");
  Serial.println(ik_TH1);
  
  Serial.print("ik_TH2: ");
  Serial.println(ik_TH2);
  
  Serial.print("ik_TH3: ");
  Serial.println(ik_TH3);

}

//void getInverseKinematics2(){
//  r2 = Z0_3 - a1;//15
//  r1 = sqrt(X0_3*X0_3 + Y0_3*Y0_3);//10
//  r3 = sqrt(r1*r1 + r2*r2);
//  thi2 = atan2(r2,r1);
//  thi1 = acos((a3*a3 - a2*a2 - r3*r3)/(-2*a2*r3));
//  thi3 = acos((r3*r3 - a2*a2 - a3*a3)/(-2*a2*a3));
//  ik_TH1 = atan2(Y0_3,X0_3)*180/PI;
//  ik_TH2 = 90 - thi2*180/PI - thi1*180/PI;
//  ik_TH3 = -(180 - thi3*180/PI);
//
//  
//  Serial.println("calculatedIK2: ");
//  Serial.print("ik2_TH1: ");
//  Serial.println(ik_TH1);
//  
//  Serial.print("ik2_TH2: ");
//  Serial.println(ik_TH2);
//  
//  Serial.print("ik2_TH3: ");
//  Serial.println(ik_TH3);
//
//}

void convertToRad(){
  
ikTH1_rad = ik_TH1/180*PI;
ikTH2_rad = ik_TH2/180*PI;
ikTH3_rad = ik_TH3/180*PI;
  
}
//mtx_type ikTT1_0[4][4] = {{0.0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
//mtx_type ikTT2_1[4][4] ={{0.0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};;
//mtx_type ikTT3_2[4][4] = {{0.0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};;
//mtx_type ikTT3_0[4][4] ={{0.0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};;
//mtx_type ikTT2_0[4][4] ={{0.0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};;
//


void calculateForwardKinematics(){
 mtx_type  ikTT1_0[4][4] = {{cos(ikTH1_rad),0,-sin(ikTH1_rad),0},
{sin(ikTH1_rad),0,cos(ikTH1_rad),0},
{0,-1,0,6},
{0,0,0,1}};

mtx_type ikTT2_1[4][4] = {{sin(ikTH2_rad),-cos(ikTH2_rad),0,sin(ikTH2_rad)*10},
{-cos(ikTH2_rad),-sin(ikTH2_rad),0,-cos(ikTH2_rad)*10},
{0,0,-1,0},
{0,0,0,1}};

mtx_type ikTT3_2[4][4] ={{cos(ikTH3_rad),-sin(ikTH3_rad),0,cos(ikTH3_rad)*15},
{sin(ikTH3_rad),cos(ikTH3_rad),0,sin(ikTH3_rad)*15},
{0,0,1,0},
{0,0,0,1}};

mtx_type ikTT3_0[4][4];
mtx_type ikTT2_0[4][4];

Serial.println("IK_calculatedForwardKinematics: ");
  Matrix.Multiply((mtx_type*)ikTT1_0, (mtx_type*)ikTT2_1, N, N, N, (mtx_type*)ikTT2_0);
  Matrix.Print((mtx_type*)ikTT2_1, N, N, "ikTT2_1");
  Matrix.Print((mtx_type*)ikTT2_0, N, N, "ikTT2_0");

  
  Matrix.Multiply((mtx_type*)ikTT2_0, (mtx_type*)ikTT3_2, N, N, N, (mtx_type*)ikTT3_0);
  Matrix.Print((mtx_type*)ikTT3_2, N, N, "ikTT3_2");
  Matrix.Print((mtx_type*)ikTT3_0, N, N, "ikTT3_0");
  
}

void calculateIK(){
  getInverseKinematics();
  convertToRad();
calculateForwardKinematics();

  
}
//




//double T1_0[4][4] = {{cos(TH1_rad),0,-sin(TH1_rad),0},
//{sin(TH1_rad),0,cos(TH1_rad),0},
//{0,-1,0,1},
//{0,0,0,1}};
//
//double T2_1[4][4] = {{cos(TH2_rad),sin(TH2_rad),0,0},
//{sin(TH2_rad),-cos(TH2_rad),0,-10},
//{0,0,-1,0},
//{0,0,0,1}};
//double T3_2[4][4] =  {{cos(TH3_rad),sin(TH3_rad),0,-3.5},
//{sin(TH3_rad),-cos(TH3_rad),0,15},
//{0,0,1,0},
//{0,0,0,1}};
//double T3_0[4][4];

mtx_type TT1_0[4][4] = {{cos(TH1_rad),0,-sin(TH1_rad),0},
{sin(TH1_rad),0,cos(TH1_rad),0},
{0,-1,0,6},
{0,0,0,1}};

mtx_type TT2_1[4][4] = {{sin(TH2_rad),-cos(TH2_rad),0,sin(TH2_rad)*10},
{-cos(TH2_rad),-sin(TH2_rad),0,-cos(TH2_rad)*10},
{0,0,-1,0},
{0,0,0,1}};
mtx_type TT2_0[4][4];

mtx_type TT3_2[4][4] =  {{cos(TH3_rad),-sin(TH3_rad),0,cos(TH3_rad)*15},
{sin(TH3_rad),cos(TH3_rad),0,sin(TH3_rad)*15},
{0,0,1,0},
{0,0,0,1}};


mtx_type TT3_0[4][4];

void calcJustFK(){

  Serial.println("just FK: ");
    Matrix.Multiply((mtx_type*)TT1_0, (mtx_type*)TT2_1, N, N, N, (mtx_type*)TT2_0);
  Matrix.Print((mtx_type*)TT2_1, N, N, "TT2_1");
  Matrix.Print((mtx_type*)TT2_0, N, N, "TT2_0");

 Matrix.Multiply((mtx_type*)TT2_0, (mtx_type*)TT3_2, N, N, N, (mtx_type*)TT3_0);
  Matrix.Print((mtx_type*)TT3_2, N, N, "TT3_2");
 Matrix.Print((mtx_type*)TT3_0, N, N, "TT3_0");

}

//void print4x4Array(double ar[4][4]){
//for(int i =0; i < 4; i++){
//  for(int j = 0; j < 4; j++){
//    Serial.print(ar[i][j]);
//    Serial.print(" ");
//  }
//  Serial.println();
//}
//Serial.println();
//}

void runservowithspeed(Servo s,int desiredAngle){
  const int angleIncrement = 1;
const int incrementDelay = 10;
int currentAngle = s.read();
if(currentAngle > desiredAngle){
  for (int angle = currentAngle; angle > desiredAngle; angle -= angleIncrement) { // single "degree" increments
 s.write(angle);
 delay (incrementDelay); // so we'll take 10 * 180 milliseconds = 1.8 seconds for the traverse.
}
}
if(currentAngle < desiredAngle){
  for (int angle = currentAngle; angle < desiredAngle; angle += angleIncrement) { // single "degree" increments
 s.write(angle);
 delay (incrementDelay); // so we'll take 10 * 180 milliseconds = 1.8 seconds for the traverse.
}
}

}


void gototheposition(Servo s1,Servo s2,Servo s3){
  if(ik_TH1> 80 || ik_TH1<-90 ||ik_TH2> 90 || ik_TH2<-60 || ik_TH3 < -65 || ik_TH3 > 85 ){
    Serial.println("cant reach this position! Danger. Achtung.");
  }else{
    runservowithspeed(s1,ik_TH1+100);
    runservowithspeed(s2,ik_TH2+60);
    runservowithspeed(s3,ik_TH3+65);
  }
}

void startposition(){
  s1.write(100);
  s2.write(65);
  s4.write(65);
}

void opengripper(){
  s6.write(30);
}
void catchgripper(){
  s6.write(100);
}


void turnonmanipulator(){
    s1.attach(3);
    s2.attach(5);
//  s3.attach(6);
    s4.attach(9);
    // EE
    s5.attach(11);
    s6.attach(10);
}
void setup() {
  Serial.begin(9600);
turnonmanipulator();
    startposition();

    
//    calcJustFK();
    calculateIK();
//    getInverseKinematics2();
//      opengripper();
    gototheposition(s1,s2,s4);
//    catchgripper();
//    delay(1500);
//    startposition();
//s2.write(120);
//s4.write(120);
    //  print4x4Array(T1_0);



}




//int  counter = 0;
void loop() {
  
  ////// init value!
 
//   s1.write(100);
//
//    runservowithspeed(s2, 60);
//
//   s4.write(65);
//
//  delay(1500);
  
}
