#include <stdlib.h>
#include "grapharm.h"

#define STEPSIZE 1 // degrees
#define MAXDEVIATION 30 // degrees

/**
 * Setup the arm servo.
*/
void setupArm(Servo *servo, int pin) {
    servo->attach(pin);
    servo->write(90);
}

/**
 * Rotate the arm towards the goal position.
 * If the arm is at the goal position, calculate a new goal.
*/
int rotateArm(Servo *servo, int pos, int *goal) {
    if (pos < *goal) {
        pos += STEPSIZE;
    } else if (pos > *goal) {
        pos -= STEPSIZE;
    } else {
        *goal = calculateGoal(pos);
    }
    servo->write(pos);
    return pos;
}

/**
 * Calculate the goal, the position the arm should move towards,
 * based on the current position. The goal is a random number
 * between 1 and MAXDEVIATION away from the current position.
 * The goal is calculated with a 1% chance of changing, and
 * a 99% chance of returning/staying on the default position.
*/
int calculateGoal(int pos) {
    // 1% chance of changing goal
    if (rand() % 100 == 0) {
        int goal = rand() % MAXDEVIATION + 1;
        rand() % 2 ? goal += pos : goal = pos - goal;
        return goal;
    }

    return 90; // default goal
}
