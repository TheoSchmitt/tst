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
//ULTROSONIC SENSOR LINE FOLLOWING PRJ 7
//ultrosonic input port 2 output port 1
while (joystickGetDigital(1, 7, JOY_DOWN)) {

distanceToTarget = ultrasonicGet(frontSonar);


printf("The distance to target is %d \n", distanceToTarget);
  errorU = (20 - distanceToTarget);
  powerU = kpU * errorU;
  if(abs(error) < maxOut){
  chassisSet (-1*powerU, -1*powerU);
}
  else {
     chassisSet(-1*powerU/abs(powerU)*maxOut,-1*powerU/abs(powerU)*maxOut);
   }

}
  if(joystickGetDigital(1,8,JOY_RIGHT)) {
    int x1 = 25;
    int y1 = 0;
    int l1 = 11;
    int l2 = 14;
    double a2;
    double a1;
    bool chk1;
    bool chk2;
    for(int x = x1; x > (x1-5); x--) { // 5 times
    chk1 = true;
    chk2 = true;
    a2 = position(x,y1,l1,l2);
    a1 = position2(a2,x,y1,l1,l2);
    a2 -= a1;
    a1 *= (180/M_PI);
    a2 *= (180/M_PI);
    while(chk1 || chk2) {
    error = (0.6*encoderGet(encoder) - a1);
    error2 = (0.5*encoderGet(encoder2) - a2);
    if((error < 42) && (error > -42)) {
    motorSet(5,error*3);
       if((-2 < error) && (error < 2)) {
    chk1 = false;
    motorSet(5,0);
    }
    } else if(error >= 42) {
    motorSet(5,127);
    } else if(error <= -42) {
    motorSet(5,-127);
    } else {
    motorSet(5,0);
    }

    if((error2 < 42) && (error2 > -42)) {
    motorSet(6,error2*3);
    if((-2 < error2) && (error2 < 2)) {
    chk1 = false;
    motorSet(6,0);
    }
    } else if(error2 >= 42) {
    motorSet(6,127);
    } else if(error2 <= -42) {
    motorSet(6,-127);
    } else {
    motorSet(6,0);
    }
    }
    }
  }



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
