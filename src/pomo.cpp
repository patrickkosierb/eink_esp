#include "pomo.h"

/* states */
extern volatile int button_state;
bool screen_state = STATE_MENU;
bool pomo_running = false;

/* pomodoro param */
int epoch = 0;
int split = 6;
int count = 0;

void pomo_task(void* param) {
  
  int break_count;
  epoch--; // TODO: bug if pause up pause without changing time 

  // run timer
  while(pomo_running && count>0){ 
    
    // update screen every min
    if(count%60==0){
      gui_time(count);
    }

    // flash led
    digitalWrite(ONBOARD_LED,HIGH);
    delay(500);
    digitalWrite(ONBOARD_LED,LOW);
    delay(500);

    count--;
    
    // break block 
    if(count%(split*60)==0 && count!=0){
      buzz();

      epoch--;
      Serial.print("Break time! Epoch remaining: ");
      Serial.println(epoch);
      break_count = BREAK_TEST;

      digitalWrite(LIFE_LED,HIGH);

      // start break
      while(pomo_running && break_count>0){
        if(break_count%60==0){
          gui_time(break_count);
        }
        delay(1000);
        break_count--;
      }
      Serial.println("Break end!");
      digitalWrite(LIFE_LED,LOW);
      buzz();
    }

  }
  // reset parameters
  Serial.println("Stopping Pomodoro timer");
  pomo_running = false;
  epoch = 0;
  gui_time(count);
  // buzz();

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
