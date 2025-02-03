#include "hw.h"
#include "pomo.h"
#include <iostream>

// states screen
volatile bool main_menu = true;
volatile bool pomo_menu = false;
volatile bool pomo_running = false;

// pomo param
int num_epoch = 1;
int split = 30;


// enter button 
volatile bool enter_pressed = false;
unsigned long lastPressTime = 0;
const int debounceDelay = 500;

void IRAM_ATTR enterISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime > debounceDelay) {
        enter_pressed = true;
        lastPressTime = currentTime;
    }
}

TaskHandle_t xPomo; 
void pomo_task(void* param) {

  while(pomo_running){
    digitalWrite(ONBOARD_LED,HIGH);
    delay(500);
    digitalWrite(ONBOARD_LED,LOW);
    delay(500);
  }

  vTaskDelete(NULL);
}


void setup() {
  init_hw();
  Serial.begin(9600);
  TaskHandle_t xlife;
  xTaskCreatePinnedToCore(life_task,"life",10000, NULL, 1,&xlife,0);
  attachInterrupt(digitalPinToInterrupt(ENTER_BUTTON), enterISR, FALLING);

}

void loop() {
  
  while(!enter_pressed);

  if(main_menu){
    enter_pressed = false;
    Serial.println("Welcome :)");
    main_menu=false;
    pomo_menu=true;
  }else if(pomo_menu && !pomo_running){
    enter_pressed = false;
    Serial.println("Starting Pomodoro timer");
    xTaskCreatePinnedToCore(pomo_task,"pomo",10000, NULL, 1,&xPomo,0);
    pomo_running = true;
  }else if(pomo_menu && pomo_running){
    enter_pressed = false;
    pomo_running = false;
    // reset screen
  }

  // buttons for session length and split

}
