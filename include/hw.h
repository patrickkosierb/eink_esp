#ifndef HW_H
#define HW_H

#include <Arduino.h>

#define ONBOARD_LED     GPIO_NUM_2
#define LIFE_LED        GPIO_NUM_22
#define GO_LED          GPIO_NUM_21
#define ENTER_BUTTON    GPIO_NUM_14
#define LENGTH_BUTTON   GPIO_NUM_13
#define SPLIT_BUTTON    GPIO_NUM_12
#define BUZZER          GPIO_NUM_32

/* button states */
#define BUTTON_DEFUALT -1
#define ENTER_PRESSED   0
#define LENGTH_PRESSED  1
#define SPLIT_PRESSED   2

/* initialize GPIO */
void init_hw(void);
/* enter button ISR */
void IRAM_ATTR enterHandleISR();
/* length button ISR */
void IRAM_ATTR lengthHandleISR();
/* split button ISR */
void IRAM_ATTR splitHandleISR();
/* life indicator task */
void life_task(void * parameter);
void start_life();
/* logic for button press */
bool pressed();
/* buzzer activate task */
void buzz_task(void * parameter);
void buzz();

#endif