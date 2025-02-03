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

bool pomo::is_on(){
    return state;
}

int pomo::get_num_epoch(){
    return num_epoch;
}
int pomo::get_split(){
    return split;
}