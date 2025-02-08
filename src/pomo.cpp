#include "pomo.h"

extern volatile bool enter_pressed;
extern volatile bool length_pressed;
extern volatile bool split_pressed;

/* states */
bool main_menu = true;
bool pomo_menu = false;
bool pomo_running = false;

// pomodoro param
int num_epoch = 1;
int split = 30;

void pomo_task(void* param) {
  while(pomo_running){
    digitalWrite(ONBOARD_LED,HIGH);
    delay(500);
    digitalWrite(ONBOARD_LED,LOW);
    delay(500);
  }
  vTaskDelete(NULL);
}

void start_pomo(){
    TaskHandle_t xPomo; 
    Serial.println("Starting Pomodoro timer");
    xTaskCreatePinnedToCore(pomo_task,"pomo",10000, NULL, 1 ,&xPomo, 0);
}

void state_machine(){

  for( ;; ){
    
    while(!pressed());

    if(enter_pressed){
      if(main_menu){
        enter_pressed = false;
        Serial.println("Welcome :)");
        main_menu=false;
        pomo_menu=true;
      }else if(pomo_menu && !pomo_running){
        enter_pressed = false;
        start_pomo();
        pomo_running = true;
      }else if(pomo_menu && pomo_running){
        enter_pressed = false;
        pomo_running = false;
        goodbye(); //test screen change
        // reset screen
      }
    }else if(length_pressed){}
    else if(split_pressed){}
    else{}
    
  }
}
