#include <stdlib.h>
#include "grapharm.h"

const uint8_t STEPSIZE = 1; // degrees
const uint8_t MAXDEVIATION = 30; // degrees

/**
 * Setup the arm servo.
*/
void setupArm(Servo *servo, uint8_t pin) {
    servo->attach(pin);
    servo->write(90);
}

/**
 * Rotate the arm towards the goal position.
 * If the arm is at the goal position, calculate a new goal.
*/
uint8_t rotateArm(Servo *servo, uint8_t pos, uint8_t *goal, uint16_t chance) {
    if (pos < *goal) {
        pos += STEPSIZE;
    } else if (pos > *goal) {
        pos -= STEPSIZE;
    } else {
        *goal = calculateGoal(pos, chance);
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
uint8_t calculateGoal(uint8_t pos, uint16_t chance) {
    if (rand() % 10000 < chance) {
        int goal = rand() % MAXDEVIATION + 1;
        rand() % 2 ? goal += pos : goal = pos - goal;
        return goal;
    }

    return 90; // default goal
}

/**
 * Update the servo chooser. The servo chooser is a struct
 * that keeps track of which servo is currently selected.
 * The servo chooser will blink the built-in LED on the
 * arduino board to indicate which servo is selected.
 * The servo chooser will blink the LED in intervals of 500ms,
 * indicating which servo is selected. The LED will then be
 * wait 3000ms before blinking again.
*/
uint8_t updateServoChooser(servochooser *sc, uint8_t delay) {
    if (sc->timer < 0) {
        if (sc->timesBlinked > sc->chosenServo + 1) {
            sc->timesBlinked = 0;
            sc->timer = 0;
            return 2;
        }
        if (sc->timer % (1000 / delay) == 0) {
            sc->timer--;
            return 1;
        }
        if (sc->timer % (500 / delay) == 0) {
            sc->timesBlinked++;
            sc->timer--;
            return 0;
        }
        sc->timer--;
        return 2;
    }
    if (sc->timer == (3000 / delay)) {
        sc->timer = -1;
    }
    else {
        sc->timer++;
    }
    return 2;
}
