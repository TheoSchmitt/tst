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


  void operatorControl() {
       int power, turn;
			 int shoulderPower;
			 int pot = 0;
       int counts;
       int target = 45;
       int Kp = 1;
       int error ;
       int power2;
       // Multiple encoders can be declared
       Encoder encoder;
      encoder = encoderInit(8, 9, false);

      homeShoulder();
encoderReset(encoder);
while(encoderGet(encoder) < 104) {
  motorSet(5,-50);
}
motorSet(5,0);
encoderReset(encoder);
while(1){
    while(joystickGetDigital(1,7, JOY_UP)) {
 error = (target - encoderGet(encoder));
 power2 = Kp * error;
motorSet(5, -power2);
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

 if(joystickGetDigital(1, 6, JOY_UP)) {
       shoulderSet(127); // pressing up, so lift should go up
     }
     else if(joystickGetDigital(1, 6, JOY_DOWN)) {
       shoulderSet(-127); // pressing down, so lift should go down
     }
     else {
       shoulderSet(0); // no buttons are pressed, stop the lift
     }
if(joystickGetDigital(1, 5, JOY_UP)) {
		   shoulderSet2(127); // pressing up, so lift should go up
		 }
		 else if(joystickGetDigital(1, 5, JOY_DOWN)) {
		   shoulderSet2(-127); // pressing down, so lift should go down
		 }
		 else {
			 shoulderSet2(0); // no buttons are pressed, stop the lift
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

 delay(200);
    }

  }
