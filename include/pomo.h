#ifndef POMO_H
#define POMO_H

#include "hw.h"
#include "gui.h"
#include "esp_log.h"

#define STATE_MENU 0
#define STATE_POMO 1 

#define BREAK_TEST 2*60
#define BREAK_SHORT 5*60
#define BREAK_LONG  10*60
/* pomodoro timer task note: this task is set to reset by clicking the start button while running */
void pomo_task(void* param);
void start_pomo();
/* state machine for device */
void state_machine();
#endif