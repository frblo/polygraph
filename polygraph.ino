#include <Servo.h>
#include "src/grapharm.h"

const int NUMSERVOS = 3;

Servo servos[NUMSERVOS];
int pos[NUMSERVOS]; // default positions
int goals[NUMSERVOS]; // default goals

/**
 * Arduino setup function. Will run once, when 
 * the arduino is powered up.
*/
void setup() {
    int pins[NUMSERVOS] = {2, 3, 4};
    for (int i = 0; i < NUMSERVOS; i++) {
        servos[i] = Servo();
        setupArm(&servos[i], pins[i]);
        pos[i] = 90;
        goals[i] = 90;
    }
}

/**
 * Arduino loop function. Will run repeatedly
 * after the setup function has run.
*/
void loop() {
    for (int i = 0; i < NUMSERVOS; i++) {
        pos[i] = rotateArm(&servos[i], pos[i], &goals[i]);
    }
    delay(6);
}
