#include "pomo.h"

extern volatile int button_state;

/* states */
bool screen_state = STATE_MENU;
bool pomo_running = false;

/* pomodoro param */
int num_epoch = 5;
int split = 30;
int count = 0;

void pomo_task(void* param) {
  
  // get total time 
  count = num_epoch*split*60; 

  // run timer
  while(pomo_running && count>0){ 

    if(count%60==0){
      gui_time(count);
    }

    digitalWrite(ONBOARD_LED,HIGH);
    delay(500);
    digitalWrite(ONBOARD_LED,LOW);
    delay(500);

    count--;
  }
  // reset param.
  pomo_running = false;
  count = 0;
  Serial.println("Stopping Pomodoro timer");
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

    switch(button_state){
      case ENTER_PRESSED:
        button_state=BUTTON_DEFUALT;
        if(screen_state==STATE_MENU){
          Serial.println("Welcome :)");
          screen_state=STATE_POMO;
        }else if(screen_state==STATE_POMO && !pomo_running){
          start_pomo();
          pomo_running = true;
        }else if(screen_state==STATE_POMO && pomo_running){
          pomo_running = false;
        }
        break;
      case LENGTH_PRESSED: // TODO: have options for STATE_MENU and STATE_POMO, maybe have a setting for show time vs not 
        button_state=BUTTON_DEFUALT;
        goodbye(); //test screen change
        break;
      case SPLIT_PRESSED:
        button_state=BUTTON_DEFUALT;
        gui_main_menu(); //back to main menu
        break;
      default:
        button_state=BUTTON_DEFUALT;
        break;
    }

  } 
}
