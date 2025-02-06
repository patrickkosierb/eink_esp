#include "hw.h"
// #include <iostream>
// #include "pomo.h"

// flags
extern volatile bool main_menu;
extern volatile bool pomo_menu;
extern volatile bool pomo_running;
extern volatile bool enter_pressed;
extern volatile bool length_pressed;
extern volatile bool split_pressed;

// pomodoro param
int num_epoch = 1;
int split = 30;

// pomodoro task
TaskHandle_t xPomo; 
void pomo_task(void* param) {

  // pomodoro timer loop
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
  
  while(!pressed());

  // hide this code in "hw.h" make it return something for starting tasks
  if(enter_pressed){
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
  }else if(length_pressed){}
  else if(split_pressed){}
  else{}

}
