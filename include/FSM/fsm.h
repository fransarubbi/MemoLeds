#ifndef FSM_H
#define FSM_H

#include <cstdint> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;
typedef enum { INIT = 0, GENERATE = 1, WAITING = 2, COMPARING = 3, ERROR = 4, CORRECT = 5 } State;


extern uint8_t level;

void init_FSM();
void update_FSM();
void match_string(uint8_t );
void clear_row(uint8_t );

#endif
