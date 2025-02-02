#include "hw.h"

void init_hw(void){
    pinMode(ONBOARD_LED,OUTPUT);
    pinMode(LIFE_LED,OUTPUT);
    pinMode(ENTER_BUTTON, INPUT_PULLUP);  
}

void life_task(void * parameter) {
  bool state_led = true;
    while (1) {
        digitalWrite(LIFE_LED,state_led);
        delay(1000);
        state_led = !state_led;
    }
}
