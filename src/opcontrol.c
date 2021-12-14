/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */


 #include "main.h"
 #include "claw.h"
 #include "chassis.h"
 #include "shoulder.h"
 #include "homeShoulder.h"
 #include "math.h"
 #include "position.h"


  void operatorControl() {
       int power, turn;
			 int shoulderPower;
			 int pot = 0;
       int counts;
       int target = 45;
       int target2 = 45;
       int Kp = 1;
       int KpL = 1;
       int error ;
       int error2;
       int power2;
       int power3;
       int lock;
       int x1 = 25;
       int y1 = 0;
       int l1 = 11;
       int l2 = 14;
       double a2;
       double a1;
       bool chk1;
       bool chk2;
       int distanceToTarget;
       int lineFL;
       int lineFM;
       int lineFR;
       analogCalibrate(1);
       analogCalibrate(2);
       analogCalibrate(3);
       // Multiple encoders can be declared
       Encoder encoder;
       Encoder encoder2;
       Ultrasonic frontSonar;
       double kpU = 0.1;
       int powerU;
       int errorU;
       int maxOut = 127;
      encoder = encoderInit(8, 9, false);
      encoder2 = encoderInit(6, 7, false);
      frontSonar = ultrasonicInit(1, 2);
      homeShoulder();
encoderReset(encoder);
while(encoderGet(encoder) < 104) {
  motorSet(5,-50);
}
motorSet(5,0);
encoderReset(encoder);


while(digitalRead(3) == HIGH) {
  motorSet(6,-50);
}
motorSet(6,0);
encoderReset(encoder2);
while(encoderGet(encoder2) > -190) {
  motorSet(6,50);
}
motorSet(6,0);
encoderReset(encoder2);
lock = 0;

while(1){
//______________________________________________________________________________

//Prj 8 Line FOLLOWING

//______________________________________________________________________________

while(joystickGetDigital(1,8,JOY_DOWN)) {
  lineFL = analogReadCalibrated(1);
  lineFM = analogReadCalibrated(2);
  lineFR = analogReadCalibrated(3);
  if(lineFM < 500 && lineFR < 500 && lineFL < 500){
  chassisSet(-50,-50);
  } else {
     if(lineFM > lineFL && lineFM > lineFR){
      chassisSet(52,52);
     } else if(lineFL < lineFR) {
         chassisSet(42,-30);
     } else if(lineFR < lineFL) {
         chassisSet(-42,30);
     }
   }
}

//______________________________________________________________________________

//ULTROSONIC SENSOR LINE FOLLOWING PRJ 7
//ultrosonic input port 2 output port 1
while (joystickGetDigital(1, 7, JOY_DOWN)) {
distanceToTarget = ultrasonicGet(frontSonar);

printf("The distance to target is %d \n", distanceToTarget);
if(distanceToTarget > 0 && distanceToTarget < 70)
{
  errorU = (20 - distanceToTarget);
  powerU = kpU * errorU;
  if(abs(error) < maxOut){
  chassisSet (-1*powerU, -1*powerU);
}
  else {
     chassisSet(-1*powerU/abs(powerU)*maxOut,-1*powerU/abs(powerU)*maxOut);
   }

}

else  {
chassisSet(-50, 50);
}
delay(50);
}
//End of Prj 7

//______________________________________________________________________________

//Prj 6 Revolute Robot Kinematics and Motion Planning

//______________________________________________________________________________
  if(joystickGetDigital(1,8,JOY_RIGHT)) {
double l1 = 10.5;
double l2 = 13.6;
double x1 = l1+l2-1;
double y1 = -2; //-1-1
double a2;
double a1;
bool chk1;
bool chk2;
for(int x = x1-1; x >= (x1-10); x--) { // 10 in
chk1 = true;
chk2 = true;
a2 = position1(x,y1,l1,l2);
a1 = position2(a2,x,y1,l1,l2);
a2 -= a1;
a1 *= (180/M_PI);
a2 *= -(180/M_PI);
//printf("\na1: %f", a1);
//printf("\na2: %f", a2);
while(chk1 || chk2) {
error = (int) round((0.6*encoderGet(encoder) - a1));
error2 = (int) round((0.5*encoderGet(encoder2) - a2));
lock = encoderGet(encoder);
//printf("\n ch1: %d",chk1);
//printf("   -    chk2: %d",chk2);
if((error < 42) && (error > -42) && chk1) {
motorSet(5,error*12);
   if((-3 < error) && (error < 3)) {
//printf("\na: %d", error);
chk1 = false;
}
//printf("a: %d", error);
//printf(" bool: %d",chk1);
} else if(error >= 42 && chk1) {
motorSet(5,127);
} else if(error <= -42 && chk1) {
motorSet(5,-127);
} else {
motorSet(5,0);
}

if((error2 < 42) && (error2 > -42) && chk2) {
motorSet(6,error2*12);
if((-3 < error2) && (error2 < 3)) {
chk2 = false;
}
} else if(error2 >= 42 && chk2) {
motorSet(6,127);
} else if(error2 <= -42 && chk2) {
motorSet(6,-127);
} else {
motorSet(6,0);
}
}
}
  }

//End of Prj 6
//______________________________________________________________________________

    while(joystickGetDigital(1,7, JOY_UP)) {
 error = (target - encoderGet(encoder));
 power2 = Kp * error;
motorSet(5, -power2);
}


while(joystickGetDigital(1,7, JOY_UP)) {
error2 = (target2 - encoderGet(encoder2));
power3 = KpL * error2;
motorSet(6, -power3);
}

        power = joystickGetAnalog(1, 2); // vertical axis on left joystick
        turn  = joystickGetAnalog(1, 1); // horizontal axis on left joystick
        chassisSet(power + turn, power - turn);

        clawSet(joystickGetAnalog(1, 4));
				clawSet2(joystickGetAnalog(1, 3));

if(joystickGetDigital(1,7, JOY_LEFT)) {
  homeShoulder();
  encoderReset(encoder);
  while(encoderGet(encoder) < 102) {
    motorSet( 5, -50);
  }
motorSet(5,0);
encoderReset(encoder);
printf("homing complete \n");
}

 if(joystickGetDigital(1, 5, JOY_UP)) {
       shoulderSet2(127);
       lock = encoderGet(encoder); // pressing up, so lift should go up
     }
     else if(joystickGetDigital(1, 5, JOY_DOWN)) {
       shoulderSet2(-127);
       lock = encoderGet(encoder); // pressing down, so lift should go down
     }
     else {
       shoulderSet2(-3*(lock-encoderGet(encoder))); // no buttons are pressed, stop the lift
     }
if(joystickGetDigital(1, 6, JOY_UP)) {
		   shoulderSet(127); // pressing up, so lift should go up
		 }
		 else if(joystickGetDigital(1, 6, JOY_DOWN)) {
		   shoulderSet(-127); // pressing down, so lift should go down
		 }
		 else {
			 shoulderSet(0); // no buttons are pressed, stop the lift
		 }
     pot = analogRead(4);
 printf("the pot value %d \n", counts);
 if (digitalRead(3) == LOW){
   print("the limit switch is pressed");
 }

     // ... Do work
     // Get encoder reading in degrees
     counts = encoderGet(encoder);
 print("the encoder is moving");
     // ... Do other work
     // Reset encoder to zero

 delay(60);
    }

  }
