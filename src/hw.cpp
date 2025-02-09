#include "hw.h"

volatile int button_state = BUTTON_DEFUALT;

unsigned long lastPressTime = 0;
const int debounceDelay = 500;

void init_hw(void){
    Serial.begin(115200);
    // gpio
    pinMode(ONBOARD_LED,OUTPUT);
    pinMode(LIFE_LED,OUTPUT);
    pinMode(ENTER_BUTTON, INPUT_PULLUP);  
    attachInterrupt(digitalPinToInterrupt(ENTER_BUTTON), enterHandleISR, FALLING);
    pinMode(LENGTH_BUTTON, INPUT_PULLUP);  
    attachInterrupt(digitalPinToInterrupt(LENGTH_BUTTON), lengthHandleISR, FALLING);
    pinMode(SPLIT_BUTTON, INPUT_PULLUP);  
    attachInterrupt(digitalPinToInterrupt(SPLIT_BUTTON), splitHandleISR, FALLING);
    // life led
    start_life();
}

void IRAM_ATTR enterHandleISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime > debounceDelay) {
        button_state = ENTER_PRESSED;
        lastPressTime = currentTime;
    }
}
void IRAM_ATTR lengthHandleISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime > debounceDelay) {
        button_state = LENGTH_PRESSED;
        lastPressTime = currentTime;
    }
}
void IRAM_ATTR splitHandleISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime > debounceDelay) {
        button_state=SPLIT_PRESSED;
        lastPressTime = currentTime;
    }
}

void life_task(void * parameter) {
    bool state_led = true;
    for( ;; ){
        digitalWrite(LIFE_LED,state_led);
        delay(1000); // TODO: make this vTaskDelay()
        state_led = !state_led;
    }
    vTaskDelete(NULL);
}
void start_life(){
    TaskHandle_t xlife;
    xTaskCreatePinnedToCore(life_task,"life",10000, NULL, 1,&xlife,0);
};

bool pressed(){
    return button_state==ENTER_PRESSED || button_state==LENGTH_PRESSED || button_state==SPLIT_PRESSED;
}