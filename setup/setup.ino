#include <Servo.h>

const int NUMSERVOS = 4; // replace with actual number of servos
const int pins[NUMSERVOS] = {2, 3, 4, 5}; // replace with 
                                          // actual pins

Servo servos[NUMSERVOS];

/**
 * Arduino setup function. Will run once, when 
 * the arduino is powered up.
*/
void setup() {
    for (int i = 0; i < NUMSERVOS; i++) {
        servos[i].attach(pins[i]);
        servos[i].write(90); // standard position
    }
}

void loop() {}
