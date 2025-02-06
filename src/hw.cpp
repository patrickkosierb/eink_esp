#include "hw.h"

volatile bool enter_pressed = false;
volatile bool length_pressed = false;
volatile bool split_pressed = false;

unsigned long lastPressTime = 0;
const int debounceDelay = 500;

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

void IRAM_ATTR enterISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime > debounceDelay) {
        enter_pressed = true;
        lastPressTime = currentTime;
    }
}

bool pressed(){
    return enter_pressed || length_pressed || split_pressed;
}