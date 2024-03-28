#include <Servo.h>

void setupArm(Servo *servo, int pin);
int rotateArm(Servo *servo, int pos, int *goal);
int calculateGoal(int pos);
