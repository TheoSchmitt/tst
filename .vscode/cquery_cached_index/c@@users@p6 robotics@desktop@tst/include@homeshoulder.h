#include "main.h"

void homeShoulder() {

printf("homing started, stand by \n");
while (digitalRead(5) == HIGH) {
  motorSet(5,50);
}
motorSet(5,0);
//shoulderEncoderAngle = -102;


// start a while loop with the condition limitSwitch == 1
//turn on shoulder in neg direction
//wait unitll limitSwitch == 1 is no longer true
//stop shoulder motor
//reset sholderEncoder
//start while loop with condition sholderEncoder < homePosition(or another home position)
//turn on shouldMoter in pos direction
//wait untill sholderEncoder < homePosition (or other home position)
//stop sholderMotor (the shoulder joint is now "homed") }



}
