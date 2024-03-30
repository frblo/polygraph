#include <Servo.h>
#include "src/grapharm.h"
#include "src/rotaryencoder.h"

const uint8_t NUMSERVOS = 3; // number of servos
const uint8_t DELAY = 5;     // delay in ms

Servo servos[NUMSERVOS];     // arm servos
uint8_t pos[NUMSERVOS];      // positions of the servos
uint8_t goals[NUMSERVOS];    // goals of the servos, 
                             // for which to move towards
uint16_t chances[NUMSERVOS]; // chances of changing the goal
                             // for each servo
servochooser sc = {0, 0};    // servo chooser

rotaryencoder re = setupRE(A0, A1, A2); // rotary encoder

/**
 * Arduino setup function. Will run once, when 
 * the arduino is powered up.
*/
void setup() {
    uint8_t pins[NUMSERVOS] = {2, 3, 4};
    for (int i = 0; i < NUMSERVOS; i++) {
        servos[i] = Servo();
        setupArm(&servos[i], pins[i]);
        pos[i] = 90;
        goals[i] = 90;
        chances[i] = 50;
    }

    pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Arduino loop function. Will run repeatedly
 * after the setup function has run.
*/
void loop() {
    for (int i = 0; i < NUMSERVOS; i++) {
        pos[i] = rotateArm(&servos[i], pos[i], &goals[i], chances[i]);
    }

    updateRE(&re);
    if (re.button.isPressed()) {
        sc.chosenServo = ++sc.chosenServo % NUMSERVOS;
        sc.timer = 0;
    }

    // Update the LED to indicate which servo is selected.
    switch (updateServoChooser(&sc, DELAY)) {
    case 0:
        digitalWrite(LED_BUILTIN, LOW);
        break;
    case 1:
        digitalWrite(LED_BUILTIN, HIGH);
        break;    
    default:
        break;
    }

    delay(DELAY); // delay to prevent flickering
}
