#include "hw.h"

/* button flags */
volatile bool enter_pressed = false;
volatile bool length_pressed = false;
volatile bool split_pressed = false;

unsigned long lastPressTime = 0;
const int debounceDelay = 500;

void init_hw(void){
    Serial.begin(115200);
    // gpio
    pinMode(ONBOARD_LED,OUTPUT);
    pinMode(LIFE_LED,OUTPUT);
    pinMode(ENTER_BUTTON, INPUT_PULLUP);  
    attachInterrupt(digitalPinToInterrupt(ENTER_BUTTON), enterISR, FALLING);
    // life led
    start_life();
}

void IRAM_ATTR enterISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime > debounceDelay) {
        enter_pressed = true;
        lastPressTime = currentTime;
    }
}

void life_task(void * parameter) {
    bool state_led = true;
    for( ;; ){
        digitalWrite(LIFE_LED,state_led);
        delay(1000); //make this vTaskDelay()
        state_led = !state_led;
    }
    vTaskDelete(NULL);
}
void start_life(){
    TaskHandle_t xlife;
    xTaskCreatePinnedToCore(life_task,"life",10000, NULL, 1,&xlife,0);
};

bool pressed(){
    return enter_pressed || length_pressed || split_pressed;
}