#include "pomo.h"

pomo::pomo(int ne, int s) {
    num_epoch = ne;
    split = s;     
}
pomo::~pomo(){}

void pomo::start(){
    state = true;
}

void pomo::stop(){
    state = false;
}

void pomo::reset(){}

bool pomo::get_state(){
    return state;
}
