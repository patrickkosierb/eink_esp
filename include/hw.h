#ifndef HW_H
#define HW_H

#include <Arduino.h>

#define ONBOARD_LED GPIO_NUM_2
#define LIFE_LED GPIO_NUM_22
#define ENTER_BUTTON  GPIO_NUM_15   

/* initialize GPIO */
void init_hw(void);
/* enter button ISR */
void IRAM_ATTR enterISR();
/* life indicator task */
void life_task(void * parameter);
void start_life();
/* logic for button press */
bool pressed();

#endif