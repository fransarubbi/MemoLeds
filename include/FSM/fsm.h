#ifndef FSM_H
#define FSM_H

#include <cstdint> 

typedef enum { INIT = 0, GENERATE = 1, WAITING = 2, COMPARING = 3, ERROR = 4, CORRECT = 5 } State;


extern uint8_t level;

void init_FSM();
void update_FSM();

#endif
