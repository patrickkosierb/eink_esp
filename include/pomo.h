#ifndef POMO_H
#define POMO_H

#include "hw.h"
#include "gui.h"
#include "esp_log.h"

#define STATE_MENU 0
#define STATE_POMO 1   

void pomo_task(void* param);
void start_pomo();
void state_machine();
#endif