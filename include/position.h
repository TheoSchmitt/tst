#include "main.h"
#include "math.h"

float position(int x1, int y1, int l1, int l2) {

int d = (x1*x1 + y1*y1 - l1*l1 - l2*l2)/(2*l1*l2);
int a1;
int a2;
a2 = atan((sqrt( 1- d*d))/d);
a1 = atan(2/x1) + atan((l2*sin(a2))/(l1+l2*cos(a2)));
a2 += a1;
}
