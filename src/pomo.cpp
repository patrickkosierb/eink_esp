#include "pomo.h"

extern volatile int button_state;

/* states */
bool screen_state = STATE_MENU;
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
      case 0:
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
      case 1:
        button_state=BUTTON_DEFUALT;
        goodbye(); //test screen change
        break;
      case 2:
        button_state=BUTTON_DEFUALT;
        helloWorld(); //test screen change
        break;
      default:
        button_state=BUTTON_DEFUALT;
        break;
    }

  } 
}
