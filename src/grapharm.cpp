#include <stdlib.h>
#include "grapharm.h"

const int STEPSIZE = 1; // degrees
const int MAXDEVIATION = 30; // degrees

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
        *goal = calculateGoal(pos, 0.01);
    }
    servo->write(pos);
    return pos;
}

/**
 * Calculate the goal, the position the arm should move towards,
 * based on the current position. The goal is a random number
 * between 1 and MAXDEVIATION away from the current position.
 * The goal is calculated with a CHANCE% chance of changing.
 * CHANCE is a float between 0 and 1 with 4 decimal places.
*/
int calculateGoal(int pos, float chance) {
    if (rand() % 10000 < int (chance * 10000)) {
        int goal = rand() % MAXDEVIATION + 1;
        rand() % 2 ? goal += pos : goal = pos - goal;
        return goal;
    }

    return 90; // default goal
}
