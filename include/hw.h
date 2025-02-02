#ifndef HW_H
#define HW_H

#include <Arduino.h>

#define ONBOARD_LED GPIO_NUM_2
#define LIFE_LED GPIO_NUM_23
#define ENTER_BUTTON  GPIO_NUM_18   


void init_hw(void);

/* life indicator task */
void life_task(void * parameter);

#endif