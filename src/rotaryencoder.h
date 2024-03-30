#include <ezButton.h>

/**
 * The rotary encoder struct keeps track of the rotary encoder.
*/
struct rotaryencoder {
    uint8_t CLK_PIN;
    uint8_t DT_PIN;
    uint8_t SW_PIN;
    ezButton button;
    int counter;
    int CLK_state;
    int last_CLK_state;

    rotaryencoder(uint8_t SW_PIN) : button(SW_PIN) {}
};

rotaryencoder setupRE(uint8_t CLK_PIN, uint8_t DT_PIN, uint8_t SW_PIN);
void updateRE(rotaryencoder *re);
