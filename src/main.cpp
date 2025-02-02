#include "hw.h"
#include "pomo.h"

// enter button 
volatile bool enter_pressed = false;
unsigned long lastPressTime = 0;
const int debounceDelay = 200;

void IRAM_ATTR enterISR() {
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime > debounceDelay) {
        enter_pressed = true;
        lastPressTime = currentTime;
    }
}

TaskHandle_t xPomo; 
void pomo_task(void * parameter) {
  // pomo::pomo(get info);  
  /*
    
   */
}

void setup() {
  init_hw();

  TaskHandle_t xlife;
  xTaskCreatePinnedToCore(life_task,"life",10000, NULL, 1,&xlife,0);
  attachInterrupt(digitalPinToInterrupt(ENTER_BUTTON), enterISR, FALLING);

}

void loop() {
  if(enter_pressed){
    Serial.println("Enter pressed");
    /*
      refresh screen 
      if we're in the menu screen (use gui.state()) then do gui.pomo()
      if we're on the pomo screen then start the timer/pomo task 
     */
  }

}
