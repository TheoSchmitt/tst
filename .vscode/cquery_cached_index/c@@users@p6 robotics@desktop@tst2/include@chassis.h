#ifndef _CHASSIS_H_
#define _CHASSIS_H_

#include "main.h"


void chassisSet(int left, int right) {
  motorSet(2, -left);
  motorSet(9, -right);

  printf("right speed %d left speed %d /n",right, left);

}

#endif
