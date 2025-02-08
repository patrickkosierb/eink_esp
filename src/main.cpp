#include "pomo.h"

void setup() {
  init_hw();
  init_gui();
}

void loop(){
  state_machine();
};
