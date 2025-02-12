#include "pomo.h"

/* states */
extern volatile int button_state;
bool screen_state = STATE_MENU;
bool pomo_running = false;

/* pomodoro param */
int epoch = 0;
int split = 30;
int count = 0;

void pomo_task(void* param) {
  // run timer
  while(pomo_running && count>0){ 

    if(count%60==0){
      gui_time(count);
    }

    if((count/60)%split==0){
      epoch--;
      Serial.print("Epoch remaining: ");
      Serial.println(epoch);

      // TODO: add a statement for split to make it an actual pomodoro timer (start another timer)
    }

    digitalWrite(ONBOARD_LED,HIGH);
    delay(500);
    digitalWrite(ONBOARD_LED,LOW);
    delay(500);

    count--;
  }
  // reset
  pomo_running = false;
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
          Serial.println("POMO menu");
          gui_time(count);
          screen_state=STATE_POMO;
        }else if(screen_state==STATE_POMO && !pomo_running){
          start_pomo();
          pomo_running = true;
        }else if(screen_state==STATE_POMO && pomo_running){
          Serial.println("POMO paused (B1)");
          pomo_running = false;
        }
        break;

      case LENGTH_PRESSED:
        button_state=BUTTON_DEFUALT;
        if(screen_state==STATE_MENU){
          // goodbye(); //test screen change
        }else if(screen_state==STATE_POMO && !pomo_running){
          epoch++;
          if(epoch>25)epoch=0; //12.5h -> split=30
          count = epoch*split*60; 
          gui_time(count);
        }else if(screen_state==STATE_POMO && pomo_running){
          Serial.println("POMO paused (B2)");
          pomo_running = false;
        }
        break;

      case SPLIT_PRESSED:
        button_state=BUTTON_DEFUALT;
        if(screen_state==STATE_MENU){
          //reset pomo param
          epoch = 0;
          count = 0;
        }else if(screen_state==STATE_POMO && !pomo_running){          
          //back to main menu
          screen_state=STATE_MENU;
          gui_main_menu();
        }else if(screen_state==STATE_POMO && pomo_running){
          Serial.println("POMO paused (B3)");
          pomo_running = false;
        }
        break;

      default:
        button_state=BUTTON_DEFUALT;
        break;
    }

  } 
}
