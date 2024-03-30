#include <Servo.h>

/**
 * The servo chooser struct keeps track of which servo 
 * is currently selected.
*/
struct servochooser {
    uint8_t chosenServo;
    short timer;
    uint8_t timesBlinked;
};

void setupArm(Servo *servo, uint8_t pin);
uint8_t rotateArm(Servo *servo, uint8_t pos, uint8_t *goal, uint16_t chance);
uint8_t calculateGoal(uint8_t pos, uint16_t chance);
uint8_t updateServoChooser(servochooser *sc, uint8_t delay);
