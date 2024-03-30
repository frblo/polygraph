#include "rotaryencoder.h"

/**
 * Setup the rotary encoder.
*/
rotaryencoder setupRE(uint8_t CLK_PIN, uint8_t DT_PIN, uint8_t SW_PIN) {
    rotaryencoder re(SW_PIN);
    re.counter = 0;
    re.CLK_PIN = CLK_PIN;
    re.DT_PIN = DT_PIN;
    pinMode(CLK_PIN, INPUT);
    pinMode(DT_PIN, INPUT);
    re.button.setDebounceTime(50);
    re.last_CLK_state = digitalRead(CLK_PIN);
    return re;
}

/**
 * Update the rotary encoder.
*/
void updateRE(rotaryencoder *re) {
    re->button.loop();
    int CLK_state = digitalRead(re->CLK_PIN);
    if (CLK_state != re->last_CLK_state && CLK_state == HIGH) {
        if (digitalRead(re->DT_PIN) == HIGH) {
            re->counter--;
        } else {
            re->counter++;
        }
    }
    re->last_CLK_state = CLK_state;
}
