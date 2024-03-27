#include <Servo.h>
#include "grapharm.h"

Servo servos[] = {Servo(), Servo(), Servo()};
int pos[] = {60, 60, 60}; // default positions
int goals[] = {60, 60, 60}; // default goals

/**
 * Arduino setup function. Will run once, when 
 * the arduino is powered up.
*/
void setup() {
    setupArm(&servos[0], 4);
    setupArm(&servos[1], 3);
    setupArm(&servos[2], 2);
}

/**
 * Arduino loop function. Will run repeatedly
 * after the setup function has run.
*/
void loop() {
    for (int i = 0; i < 3; i++) {
        pos[i] = rotateArm(&servos[i], pos[i], &goals[i]);
    }
    delay(6);
}
